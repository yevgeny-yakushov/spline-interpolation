# Сплайн интерполяция qt/c++

Позволяет легко произвести сплайн интерполяцию с консольным выводом расчетов, а также графическим отображением исходной функции, интерполяции и ошибкой интерполяции.

Пример:

```cpp
    // Устанавливаем разбиение на количество отрезков
    #define DOT_AMOUNT          100
    // Устанавливаем границы
    #define LEFT_POINT_RANGE    1.0
    #define RIGHT_POINT_RANGE   6.0
    
    // Определяем исходную функцию
    double func(double x) { return qLn(x); };
    
    int main(int argc, char *argv[])
    {
        QApplication app(argc, argv);
    
        CCreateSpline spline(func, LEFT_POINT_RANGE, RIGHT_POINT_RANGE, DOT_AMOUNT);
    
        return app.exec();
    }
```

# Вывод

Все расчеты будут выведены в консоль, пример:

![Пример консольного вывода](https://github.com/yevgeny-yakushov/spline-interpolation/raw/main/Output/console.png)

Пример графиков:

![График сплайн интерполяции](https://github.com/yevgeny-yakushov/spline-interpolation/raw/main/Output/graph.png)