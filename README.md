# Esteganografía
La esteganografía es la práctica de ocultar información dentro de otro objeto de forma tal que su detección no sea posible a simple vista.

Este repositorio fue creado para desarrollar un programa en C que permita tanto ocultar una imagen .bmp en otras, como recuperar la imagen a partir de las otras. Para esto se siguió el paper ['(k,n) secret image sharing scheme capable of cheating detection'](https://jwcn-eurasipjournals.springeropen.com/articles/10.1186/s13638-018-1084-7#Sec8) de Yan-Xiao Liu, Quin-Dong Sun y Ching-Nung Yang.

Trabajo práctico para la materia '72.44- Criptografía y Seguridad'.

## Prerrequisitos
* [Compilador C](https://gcc.gnu.org/)

## Compilar el proyecto
Se cuenta con un archivo Makefile.

Para limpiar los archivos de compilación:
```
make clean
```
Para compilar:
```
make all
```
Este comando crea el ejecutable en la carpeta bin

## Correr el proyecto
Se pueden realizar dos acciones:

1. Esconder una imagen en otras n, logrando un esquema de secreto compartido (k, n). Desde el directorio bin:
```
./ss d path/imagen.bmp k path_sombras
```
Donde:    
* d: especifica que se va a distribuir la imagen
* path/imagen.bmp: path a la imagen a distribuir
* k: cantidad mínima de sombras que se necesitarán para reconstruir el secreto
* path_sombras: path donde se encuentran las imágenes que tendrán las sombras del secreto

2. Recuperar el secreto a partir de n sombras. Desde el directorio bin:
```
./ss r path/imagen.bmp k path_sombras
```
Donde:
* r: especifica que se va a recuperar la imagen
* path/imagen.bmp: archivo de salida donde se recuperará el secreto
* k: mínima cantidad de sombras requeridas para recuperar el secreto
* path_sombras: path donde se encuentran las sombras que contienen las sombras del secreto

## Consideraciones
* Se debe respetar el orden de los parámetros
* Al ser un esquema de secreto compartido (k, n), es necesario que:
    * en el directorio donde se guardarán las sombras haya al menos k imágenes
    * en el directorio desde el que se toman las sombras haya al menos k imágenes