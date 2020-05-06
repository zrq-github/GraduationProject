#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{
public:
    Student();
    void setId(int id);
    int id();
    void setName(const QString &name);
    QString name();

private:
    int m_id;
    QString m_name;
};

#endif // STUDENT_H