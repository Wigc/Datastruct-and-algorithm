#pragma once

template<class T>
class SimNode
{

    friend SimSpace<T>;

private:
    T data;
    int link;
};