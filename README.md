# tzposix
Get the timezone posix string from GPS coordinates

The software of some microcontrollers follows the POSIX standard of local time setting. This means that you must set the environment variable *“TZ”* with [setenv](http://man7.org/linux/man-pages/man3/setenv.3.html) and then call [tzset](http://man7.org/linux/man-pages/man3/tzset.3.html) de la liberia *time*.  
tzposix.c is a CGI to convert the geographic location (lat, long) into the necessary POSIX string for the TZ environment variable. Returns a json containing the timezone Olson and POSIX version given certain GPS coordinates. Once compiled and downloaded in the cgi-bin directory of your web server, it is invoked as follows:  
<center>

    https://yourserver/cgi-bin/tzposix?lat=[float]&lon=[float]

</center>
Example:  
<center>

    https://sotech.es/cgi-bin/tzposix?lat=40.4165000&lon=-3.7025600

</center>

returns the following JSON:
<center>

    {"olson": "Europe/Madrid", "posix": "CET-1CEST,M3.5.0,M10.5.0/3"}

</center>

Source code is inspired by the work of [Bertold Van den Bergh](https://github.com/BertoldVdb/ZoneDetect).  Contains instructions for the generation of the timezone geographic databases ([timezone16.bin](./timezone16.bin) y [timezone21.bin](./timezone21.bin)) en [Database Generation](https://github.com/BertoldVdb/ZoneDetect/database).

[Timezone Boundary Builder](https://github.com/evansiroky/timezone-boundary-builder) is the basis for generating the databases. You can also find software for several languages (C, Javascript, Python, PHP, etc).

File [tzinfo.json](./tzinfo.json)  contains the correspondence table between the Olson format and the POSIX format. Instructions for creating it are in [pgurenko](https://github.com/pgurenko/tzinfo).
# Update
Each time the [TimeZone DataBase](https://www.iana.org/time-zones) is changed, files [timezone16.bin](./timezone16.bin) o [timezone21.bin](./timezone21.bin) as well as [tzinfo.json](./tzinfo.json) must be updated.
You can [subscribe](http://mm.icann.org/mailman/listinfo/tz-announce) to the mailing list where updates are announced.


