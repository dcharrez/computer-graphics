# 2.4 Ejercicios

## 2.4.1

### Running

```bash
g++ main.cpp -lglut -lGL -lGLEW -lGLU
```

### Screenshots

![alt text](https://github.com/uddua/computer-graphics/blob/master/book_exercises/section_2.4/2.4.1_img_1.png)

![alt text](https://github.com/uddua/computer-graphics/blob/master/book_exercises/section_2.4/2.4.1_img_2.png)

## 2.4.2



## 2.4.3

```c
pen_up() {

}

pen_down() {

}

locate(dcx, dcy) {

}
```

## 2.4.4

### Aspectos graficos, fisicos, resolucion horizontal y vertical de una TV donde:

* ancho = 42 cm
* alto = 31 cm
* ndh = 546
* ndv = 434

```c
resolucion_horizontal = 546 / 420;
resolucion_vertical = 434 / 310;
total_de_puntos_direccionables = 546 * 434;
resolucion_de_area = total_de_puntos_direccionables / (420/546);
razon_de_aspecto = (310/546) / (420/434);
razon_de_aspecto_fisico = 310 / 420;
```


