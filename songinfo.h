#ifndef SONGINFO_H
#define SONGINFO_H

#include <QString>

class SongInfo
{
public:
    SongInfo();
    SongInfo(QString, QString, QString, QString);
    void setId(QString);
    QString getId() const;
    void setTitle(QString);
    QString getTitle() const;
    void setAuthor(QString);
    QString getAuthor() const;
    void setLength(QString);
    QString getLength() const;

private:
    QString id, title, author, length;
};

#endif // SONGINFO_H
