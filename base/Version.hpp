//
// Created by 岳子剑 on 2020/01/09.
//


#ifndef BLIENT__BASE__VERSION__HPP
#define BLIENT__BASE__VERSION__HPP


class Version
{
public:
    Version() = default;

    inline Version( int major, int minor, int patch );

    [[nodiscard]] inline int Major() const;
    [[nodiscard]] inline int Minor() const;
    [[nodiscard]] inline int Patch() const;

    inline bool operator ==( const Version& version );
    inline bool operator !=( const Version& version );

    inline bool operator <( const Version& version );
    inline bool operator >( const Version& version );

private:
    int major_ = 0;
    int minor_ = 0;
    int patch_ = 0;
};


#include "Version.inl"


#endif
