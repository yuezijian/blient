
const QWebChannelMessageTypes =
    {
        signal: 1,
        propertyUpdate: 2,
        init: 3,
        idle: 4,
        debug: 5,
        invokeMethod: 6,
        connectToSignal: 7,
        disconnectFromSignal: 8,
        setProperty: 9,
        response: 10,
    };


class QWebChannel
{
    constructor()
    {
        this.id = 0;
        this.callbacks = {};

        this.objects = {};

        this.transport = window.qt.webChannelTransport;

        this.transport.onmessage = (message) =>
        {
            let data = message.data;

            if (typeof data === 'string')
            {
                data = JSON.parse(data);
            }

            switch (data.type)
            {
                case QWebChannelMessageTypes.signal:
                    this.handle_signal(data);
                    break;
                case QWebChannelMessageTypes.response:
                    this.handle_response(data);
                    break;
                case QWebChannelMessageTypes.propertyUpdate:
                    this.handle_property_update(data);
                    break;
                default:
                    console.error('invalid message received: ', message.data);
                    break;
            }
        };
    }

    send(data)
    {
        if (typeof(data) !== 'string')
        {
            data = JSON.stringify(data);
        }

        this.transport.send(data);
    }

    execute(data, callback)
    {
        if (callback)
        {
            if (this.id === Number.MAX_VALUE)
            {
                this.id = Number.MIN_VALUE;
            }

            if (data.hasOwnProperty('id'))
            {
                console.error("Cannot execute message with property id: " + JSON.stringify(data));

                return;
            }

            data.id = this.id++;

            this.callbacks[data.id] = callback;
        }

        this.send(data);
    }

    handle_signal(message)
    {
        const object = this.objects[message.object];

        if (object)
        {
            object.signalEmitted(message.signal, message.args);
        }
        else
        {
            console.warn("Unhandled signal: " + message.object + "::" + message.signal);
        }
    }

    handle_response(message)
    {
        if (message.hasOwnProperty("id"))
        {
            this.callbacks[message.id](message.data);

            delete this.callbacks[message.id];
        }
        else
        {
            console.error("Invalid response message received: ", JSON.stringify(message));
        }
    }

    handle_property_update(message)
    {
        for (const i in message.data)
        {
            const data = message.data[i];

            const object = this.objects[data.object];

            if (object)
            {
                object.propertyUpdate(data.signals, data.properties);
            }
            else
            {
                console.warn("Unhandled property update: " + data.object + "::" + data.signal);
            }
        }

        this.execute({type: QWebChannelMessageTypes.idle});
    }

    debug(message)
    {
        this.send({type: QWebChannelMessageTypes.debug, data: message});
    }
}


function QObject(name, data, webChannel)
{
    this.__id__ = name;

    webChannel.objects[name] = this;

    // List of callbacks that get invoked upon signal emission
    this.__objectSignals__ = {};

    // Cache of all properties, updated when a notify signal is emitted
    this.__propertyCache__ = {};

    var object = this;

    // ----------------------------------------------------------------------

    this.unwrapQObject = function(response)
    {
        if (response instanceof Array)
        {
            // support list of objects
            var ret = new Array(response.length);
            for (var i = 0; i < response.length; ++i)
            {
                ret[i] = object.unwrapQObject(response[i]);
            }
            return ret;
        }
        if (!response
            || !response["__QObject*__"]
            || response.id === undefined)
        {
            return response;
        }

        var objectId = response.id;

        if (webChannel.objects[objectId])
            return webChannel.objects[objectId];

        if (!response.data)
        {
            console.error("Cannot unwrap unknown QObject " + objectId + " without data.");
            return;
        }

        var qObject = new QObject( objectId, response.data, webChannel );

        qObject.destroyed.connect(function() {
            if (webChannel.objects[objectId] === qObject)
            {
                delete webChannel.objects[objectId];
                // reset the now deleted QObject to an empty {} object
                // just assigning {} though would not have the desired effect, but the
                // below also ensures all external references will see the empty map
                // NOTE: this detour is necessary to workaround QTBUG-40021
                var propertyNames = [];
                for (var propertyName in qObject)
                {
                    propertyNames.push(propertyName);
                }
                for (var idx in propertyNames)
                {
                    delete qObject[propertyNames[idx]];
                }
            }
        });
        // here we are already initialized, and thus must directly unwrap the properties
        qObject.unwrapProperties();

        return qObject;
    }

    this.unwrapProperties = function()
    {
        for (var propertyIdx in object.__propertyCache__) {
            object.__propertyCache__[propertyIdx] = object.unwrapQObject(object.__propertyCache__[propertyIdx]);
        }
    }

    function addSignal(signalData, isPropertyNotifySignal)
    {
        var signalName = signalData[0];
        var signalIndex = signalData[1];

        object[signalName] =
            {
                connect: function(callback)
                {
                    if (typeof(callback) !== "function")
                    {
                        console.error("Bad callback given to connect to signal " + signalName);
                        return;
                    }

                    object.__objectSignals__[signalIndex] = object.__objectSignals__[signalIndex] || [];
                    object.__objectSignals__[signalIndex].push(callback);

                    if (!isPropertyNotifySignal && signalName !== "destroyed")
                    {
                        // only required for "pure" signals, handled separately for properties in propertyUpdate
                        // also note that we always get notified about the destroyed signal
                        webChannel.execute({
                            type: QWebChannelMessageTypes.connectToSignal,
                            object: object.__id__,
                            signal: signalIndex
                        });
                    }
                },
                disconnect: function(callback)
                {
                    if (typeof(callback) !== "function")
                    {
                        console.error("Bad callback given to disconnect from signal " + signalName);
                        return;
                    }
                    object.__objectSignals__[signalIndex] = object.__objectSignals__[signalIndex] || [];
                    var idx = object.__objectSignals__[signalIndex].indexOf(callback);

                    if (idx === -1)
                    {
                        console.error("Cannot find connection of signal " + signalName + " to " + callback.name);
                        return;
                    }
                    object.__objectSignals__[signalIndex].splice(idx, 1);

                    if (!isPropertyNotifySignal && object.__objectSignals__[signalIndex].length === 0)
                    {
                        // only required for "pure" signals, handled separately for properties in propertyUpdate
                        webChannel.execute({
                            type: QWebChannelMessageTypes.disconnectFromSignal,
                            object: object.__id__,
                            signal: signalIndex
                        });
                    }
                }
            };
    }

    /**
     * Invokes all callbacks for the given signalname. Also works for property notify callbacks.
     */
    function invokeSignalCallbacks(signalName, signalArgs)
    {
        var connections = object.__objectSignals__[signalName];

        if (connections)
        {
            connections.forEach(function(callback)
            {
                callback.apply(callback, signalArgs);
            });
        }
    }

    this.propertyUpdate = function(signals, propertyMap)
    {
        // update property cache
        for (var propertyIndex in propertyMap)
        {
            var propertyValue = propertyMap[propertyIndex];
            object.__propertyCache__[propertyIndex] = propertyValue;
        }

        for (var signalName in signals)
        {
            // Invoke all callbacks, as signalEmitted() does not. This ensures the
            // property cache is updated before the callbacks are invoked.
            invokeSignalCallbacks(signalName, signals[signalName]);
        }
    }

    this.signalEmitted = function(signalName, signalArgs)
    {
        invokeSignalCallbacks(signalName, this.unwrapQObject(signalArgs));
    }

    function addMethod(methodData)
    {
        var methodName = methodData[0];
        var methodIdx = methodData[1];
        object[methodName] = function() {
            var args = [];
            var callback;
            for (var i = 0; i < arguments.length; ++i)
            {
                var argument = arguments[i];
                if (typeof argument === "function")
                    callback = argument;
                else if (argument instanceof QObject && webChannel.objects[argument.__id__] !== undefined)
                    args.push({
                        "id": argument.__id__
                    });
                else
                    args.push(argument);
            }

            webChannel.execute({
                "type": QWebChannelMessageTypes.invokeMethod,
                "object": object.__id__,
                "method": methodIdx,
                "args": args
            }, function(response) {
                if (response !== undefined) {
                    var result = object.unwrapQObject(response);
                    if (callback) {
                        (callback)(result);
                    }
                }
            });
        };
    }

    function bindGetterSetter(propertyInfo)
    {
        var propertyIndex = propertyInfo[0];
        var propertyName = propertyInfo[1];
        var notifySignalData = propertyInfo[2];
        // initialize property cache with current value
        // NOTE: if this is an object, it is not directly unwrapped as it might
        // reference other QObject that we do not know yet
        object.__propertyCache__[propertyIndex] = propertyInfo[3];

        if (notifySignalData)
        {
            if (notifySignalData[0] === 1)
            {
                // signal name is optimized away, reconstruct the actual name
                notifySignalData[0] = propertyName + "Changed";
            }
            addSignal(notifySignalData, true);
        }

        Object.defineProperty(object, propertyName, {
            configurable: true,
            get: function () {
                var propertyValue = object.__propertyCache__[propertyIndex];
                if (propertyValue === undefined) {
                    // This shouldn't happen
                    console.warn("Undefined value in property cache for property \"" + propertyName + "\" in object " + object.__id__);
                }

                return propertyValue;
            },
            set: function(value)
            {
                if (value === undefined)
                {
                    console.warn("Property setter for " + propertyName + " called with undefined value!");
                    return;
                }

                object.__propertyCache__[propertyIndex] = value;

                let valueToSend = value;

                if (valueToSend instanceof QObject && webChannel.objects[valueToSend.__id__] !== undefined)
                {
                    valueToSend = { "id": valueToSend.__id__ };
                }

                webChannel.execute({
                    "type": QWebChannelMessageTypes.setProperty,
                    "object": object.__id__,
                    "property": propertyIndex,
                    "value": valueToSend
                });
            }
        });

    }

    // ----------------------------------------------------------------------

    data.methods.forEach(addMethod);

    data.properties.forEach(bindGetterSetter);

    data.signals.forEach(function(signal) { addSignal(signal, false); });

    for (var name1 in data.enums)
    {
        object[name1] = data.enums[name1];
    }
}


function create_channel(object, callback)
{
    const channel = new QWebChannel();

    const setup = (data) =>
    {
        for (const name in data)
        {
            new QObject(name, data[name], channel);
        }

        for (const name in channel.objects)
        {
            channel.objects[name].unwrapProperties();
        }

        if (callback)
        {
            callback(channel.objects[object]);
        }

        channel.execute({ type: QWebChannelMessageTypes.idle });
    };

    channel.execute({ type: QWebChannelMessageTypes.init }, setup);
}

// window.Blient =
//     {
//         init(callback)
//         {
//             create_channel('blient', callback);
//         }
//     };


window.Blient = function ()
{
    let blient = null;

    create_channel('blient', object => blient = object);

    return blient;
}