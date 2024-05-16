# GOOP - Generic Object Oriented Programming in 'C'
- Object Oriented Programming in "C"
- see 'tests/' for examples

## TODO
- rename functions: _overrides, __local_private
- move the 'context' to GObjStatics
- collect all the G* folders under "goop" and deliver to DrFrancitosh.git
- add onException to GObj (or should I just override the "throw" method?)

## Big Ideas
- There are three elements of OOP: Encapsulation, Inheritance, and Polymorphism
- Encapsulation: all the parts of an object are in one structure (member instance variables (state) and methods (behavior))
- Polymorphism: the ability of an object's behavior to be specific to that object's type
- Inheritance: the ability to extend a class from a super class

## PROS
1. Uses no external compilers, transpilers, language translators, or interpretters
1. Only uses conventions
1. Looks very C++ like without the overhead of C++
1. Improves on memory allocation by using Goop alloc() and eliminating "free()" calls
1. IDEs still work well and offer "hinting"

## CONS
1. The conventions are a bit arcane and prone to error
    1. It's easy to forget to add "\" at the end of a macro's line
1. No memory bounds checks - but that's a "C" problem, not a Goop problem
1. No "reference counts
1. IDEs get confused
1. No functional programming (object chaining)
    1. EG: NOT THIS: `_(obj)->foo()->bar()->baz()`
1. Name spaces can be a problem for Members and Methods
    1. for example: "type" as a type name is fine
    1. but if a subclass also creates a member called 'type' then there is a conflict
1. You cannot overload Method names
    1. for example: if you create a method "G_METHOD(int, foo)(int a)"
    2. then you have a subclass with a method "G_METHOD(char *, foo)(int a)"
    3. You will get an error as you have two members with the same name
1. You also cannot override methods with new data types
    1. the signature of overridden methods must match exactly
    1. one way to get around this is the have empty argument lists
    1. for example: "G_METHOD(int, foo)()" will have no arguments, 
    1. so the caller can can pass any number of parameters
1. You cannot nest calls to object methods
    1. `_(led)->put(_(button)->get())`
    1. This will set _THAT_ to `button` by the time the `put()` method is called
1. There is no concept of an "interface" which allows a class to "look" like another class
    1. Example: the "BoardButton" has no GPIO pin, So having it emulate GPioOutput is problematic
## The Traditional Way: Drawing Shapes

```C
void point_draw(int x, int y, int color) {
    set_color(color);
    set_pixel(x, y);
}

void rectangle_draw(int x, int y, int w, int h, int color) {
    set_color(color);
    moveto(x, y);
    rect(w, h);
}

void square_draw(int x, int y, int w, int color) {
    rectangle_draw(x, y, w, w, color);
}

void oval_draw(int x, int y, int w, int h, int color) {
    set_color(color);
    moveto(x, y);
    oval(w, h);
}

void circle_draw(int x, int y, int w, int h, int color) {
    set_color(color);
    moveto(x, y);
    oval(w, h);
}

typedef struct Shape {
    int type;
    int x, y, w, h, color;
}

enum ShapeType {
    POINT = 1,
    SQUARE,
    RECTANGLE,
    OVAL,
    CIRCLE
}
void draw_shape(Shape *shape) {
    switch(shape->type) {
        case(POINT): point_draw(shape->x, shape->y, shape->color); break;
        case(SQUARE): square_draw(shape->x, shape->y, shape->w, shape->color); break;
        case(RECTANGLE): rectangle_draw(shape->x, shape->y, shape->w, shape->h, shape->color); break;
        case(CIRCLE): circle_draw(shape->x, shape->y, shape->w, shape->color); break;
        case(OVAL): oval_draw(shape->x, shape->y, shape->w, shape->color); break;
        default: printf("ERROR: Uknown Shape: %d", shape->type); 
    }
}

Shape *Shape_new(int type, int x, int y, int w, int h, int color) {
    Shape *shape = (Shape *) calloc(1, sizeof(Shape));
    return shape;
}

int main(int argc, char **argv) {
    Shape *point = Shape_new(POINT, 50, 50, -1, -1, BLACK);
    Shape *square = Shape_new(SQUARE, 50, 100, 25, -1, BLACK);
    Shape *rectangle = Shape_new(RECTANGLE, 100, 100, 50, 25, BLACK);
    Shape *circle = Shape_new(CIRCLE, 50, 200, 25, -1, BLACK);
    Shape *oval = Shape_new(CIRCLE, 100, 200, 25, 50, BLACK);

    Shape_draw(point);
    Shape_draw(square);
    Shape_draw(rectangle);
    Shape_draw(circle);
    Shape_draw(oval);
}
```

## Implementation Details
- Using `struct` to define a class's instance variables, we can build up the class's inheritance
- And using `#define` we can reuse a class's members in subclasses

In the following sections we'll use a simple graphics drawing system to demonstrate the implementation of our OOP system.

### Encapsulation: `struct` as a mechanism for encapsulation
```C
typedef struct Shape {
    int x;
    int y;
    int color;
    void (*draw)(Shape *this); // method to draw object
} Shape;

Shape *Shape_new(int x, int y, int color) {
    Shape *this = calloc(1, sizeof(Shape));
    this->x = x;
    this->y = y;
    this->color = color;
    this->draw = Shape_draw();
}

void Shape_draw(Shape *this) {
    moveto(this->x,this->y);
    setPixel(this->color):
}

int main(int argc, void *argv) {
    Shape *point = Shape_new(50, 50, RED);
    point->draw(point);
}
```

In this example we have a `struct` called `Shape`. Using the 'C' `struct` allows us to collect (or encapsulate) all the elements of the `Shape` into a block of memory. Notice that we include the function `draw` as well. By keeping the functions that operate on an object - *with* the object, we simplify access to the methods. It's clear what "verbs" or "behavior" are available to act on our objects. As such `struct Shape` is a simple implementation of a `class`.

There are two types of "members" in a class. 

"Instance" variables are values that hold the "state" of the object. In our `Shape` class we have three instance variables: x, y, and color. These hold the location of the object on the screen 

"Methods" are functions that operate on the instance variables and change the state of the object. In the case of the `Shape` we have the `draw()` method. It w

The `Shape_new()` function is a "constructor" that allocates memory for the instance object, initializes the state variables, and assigns function pointers to the methods variables. When we call a constructor like `Shape_new()` it is said we are "instantiating" the class (or creating an instance of the class).

Now that we have an instance of the `Shape` class called `point`, we can call one of its methods. In the `main()` program, you can see the instantiation of the `Shape` followed by calling of the `draw()` method by referencing the `point` object pointer.
In this case, we pass the `point` object into the `draw()` method so that it knows which `Shape` to operate on.

Inside the `draw()` method, our `point` is been passed in as the argument to `this`. Now we can move the graphics cursor using `move(this->, this->y);` and draw a single pixel with the `point(this->color)` call.

Next, let's expand on this implementation to include drawing a rectangle.

## Polymorphism: an alternative to case statements

```C
// adding the following to our earlier example:
typedef struct Square {
    int x;
    int y;
    int color;
    void (*draw)(Square *this); // method to draw object
    int w;
} Square;

Square *Square_new(int x, int y, int w, int color) {
    Square *this = calloc(1, sizeof(Square));
    this->x = x;
    this->y = y;
    this->w = w;
    this->color = color;
    this->draw = Square_draw();
}

void Square_draw(Square *this) {
    setColor(this->color):
    moveto(this->x,this->y);
    rect(this->x,this->y, this->w, this->w);    
}

typedef struct Rectangle {
    int x;
    int y;
    int color;
    void (*draw)(Rectangle *this); // method to draw object
    int w;
    int h;
} Rectangle;

Rectangle *Rectangle_new(int x, int y, int w, int h, int color) {
    Shape *this = calloc(1, sizeof(Rectangle));
    this->x = x;
    this->y = y;
    this->y = w;
    this->y = h;
    this->color = color;
    this->draw = Rectangle_draw();
}

void Rectangle_draw(Rectangle *this) {
    setColor(this->color):
    moveto(this->x,this->y);
    rect(this->x,this->y, this->w, this->h);
}

int main(int argc, void *argv) {
    Shape *point = Shape_new(50, 50, RED);
    point->draw(point);
}

```



