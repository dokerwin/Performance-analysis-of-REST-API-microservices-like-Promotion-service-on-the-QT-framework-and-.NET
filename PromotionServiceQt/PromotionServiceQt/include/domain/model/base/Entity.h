#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
    explicit Entity(int id) : id(id) {}

    int getId() const { return id; }
    void setId(const int& value) { id = value; }

private:
    int id;
};

#endif // ENTITY_H
