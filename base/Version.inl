//
// Created by 岳子剑 on 2020/01/09.
//


Version::Version( int major, int minor, int patch )
    : major_( major ), minor_( minor ), patch_( patch )
{
}

int Version::Major() const
{
    return this->major_;
}

int Version::Minor() const
{
    return this->minor_;
}

int Version::Patch() const
{
    return this->patch_;
}

bool Version::operator ==( const Version& version )
{
    return
        this->major_ == version.major_ &&
        this->minor_ == version.minor_ &&
        this->patch_ == version.patch_
        ;
}

bool Version::operator !=( const Version& version )
{
    return
        this->major_ != version.major_ ||
        this->minor_ != version.minor_ ||
        this->patch_ != version.patch_
        ;
}

bool Version::operator <( const Version& version )
{
    if ( this->major_ < version.major_ )
    {
        return true;
    }

    if ( this->major_ > version.major_ )
    {
        return false;
    }

    if ( this->minor_ < version.minor_ )
    {
        return true;
    }

    if ( this->minor_ > version.minor_ )
    {
        return false;
    }

    return this->patch_ < version.patch_;
}

bool Version::operator >( const Version& version )
{
    if ( this->major_ > version.major_ )
    {
        return true;
    }

    if ( this->major_ < version.major_ )
    {
        return false;
    }

    if ( this->minor_ > version.minor_ )
    {
        return true;
    }

    if ( this->minor_ < version.minor_ )
    {
        return false;
    }

    return this->patch_ > version.patch_;
}
