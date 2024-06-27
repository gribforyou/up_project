#include "songinfo.h"

SongInfo::SongInfo()
{

}

SongInfo::SongInfo(QString id, QString title, QString author, QString length)
{
    this->id = id;
    this->title = title;
    this->author = author;
    this->length = length;
}

void SongInfo::setId(QString id)
{
    this->id = id;
}

QString SongInfo::getId() const
{
    return id;
}

void SongInfo::setTitle(QString title)
{
    this->title = title;
}

QString SongInfo::getTitle() const
{
    return title;
}

void SongInfo::setAuthor(QString author)
{
    this->author = author;
}

QString SongInfo::getAuthor() const
{
    return author;
}

void SongInfo::setLength(QString length)
{
    this->length = length;
}

QString SongInfo::getLength() const
{
    return length;
}
