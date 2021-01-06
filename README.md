[![Build Status](https://travis-ci.com/DaniilRyb/lab-03-shared-ptr.svg?branch=lab-work-3)](https://travis-ci.com/DaniilRyb/lab-03-shared-ptr)
# Лабораторная работа №3

### Задание

**SharedPtr** реализует подсчет ссылок на ресурс. Ресурс освободится тогда, когда счетчик ссылок на него будет равен 0. Как видно, система реализует одно из основных правил сборщика мусора.
Реализуйте шаблон класса `SharedPtr`. Для счетчика ссылок используйте переменную класса `std::atomic_uint`. Интерфейс работы с этим классом аналогичен работе с переменной типа `unsigned int`, т.е. к нему применимы операции префиксного инкремента и декремента.

```cpp
template <typename T>
class SharedPtr {
public:
    SharedPtr();
    SharedPtr(T* ptr);
    SharedPtr(const SharedPtr& r);
    SharedPtr(SharedPtr&& r);
    ~SharedPtr();
    auto operator=(const SharedPtr& r) -> SharedPtr&;
    auto operator=(SharedPtr&& r) -> SharedPtr&;

    // проверяет, указывает ли указатель на объект
    operator bool() const;
    auto operator*() const -> T&;
    auto operator->() const -> T*;
    
    auto get() -> T*;
    void reset();
    void reset(T* ptr);
    void swap(SharedPtr& r);
    // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t;
};
```

### Рекомендации
Подробное объяснение об устройстве `shared_ptr` можно прочитать в книге "Эффективный и современный С++" Скотта Мейерса или на соответсвующей лекции по Алгоритмическим Языкам. 
