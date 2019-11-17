# Segundo laboratorio de Computación Grafica - CS UNSA 2019

Alumno:
- Jair Francesco Huaman Canqui
- CUI: 20152567

Profesor: 
- Dr. Juan Carlos Gutierrez Caceres

Para compilar el programa usar el .sh
```
sh compile.sh
```

Luego ejecute con

```
./lab2
```

# 1. Mover la camara con el Mouse

## Movimiento usando el rastro del mouse
![grafica_linea](imagenes/mov_movmouse.gif)

## Movimiento pulsando un click
![grafica_linea](imagenes/mov_clickmouse.gif)

# 2. Dotar al programa de una tecla que permita cambiar el modo de proyección entre ORTOGONAL y PERSPECTIVA
Para cambiar de modo de proyección usar la tecla F7, es un switch entre ambos modos


```
case GLUT_KEY_F7:
    if(MiCamara->camProjection == CAM_CONIC){
        MiCamara->x1=-3;
        MiCamara->x2=3;
        MiCamara->y1=-3;
        MiCamara->y2=3;
        MiCamara->z1=-5;
        MiCamara->z2=5;
        MiCamara->camProjection = CAM_PARALLEL;
    } else MiCamara->camProjection = CAM_CONIC;
    break;
```
![grafica_circunferencia](imagenes/cambio_perspectiva.gif)

# 3. Mover el objeto en la proyeccion (con las teclas)

![grafica_traslacion](imagenes/mov_teclas.gif)


# 4. Programar otros modos de movimiento de cámara como son el MODO PAN o el MODO TRÍPODE

![rellenado_poligonos](imagenes/grafica_rellenadopoligono.png)


