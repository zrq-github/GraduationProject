#include "student.h"

Student::Student()
{
    m_id = 0;
    m_name = "";
}

void Student::setId(int id)
{
    this->m_id = id;
}

int Student::id()
{
    return this->m_id;
}

void Student::setName(const QString &name)
{
    this->m_name = name;
}

QString Student::name()
{
    return this->m_name;
}