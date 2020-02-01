# tzposix
Get the timezone posix string from GPS coordinates

El software de algunos microcontroladores siguen el standard POSIX de ajuste de hora local. Esto quiere decir que debes ajustar la variable de entorno "TZ" con [setenv](http://man7.org/linux/man-pages/man3/setenv.3.html) y luego llamar a [tzset](http://man7.org/linux/man-pages/man3/tzset.3.html).
