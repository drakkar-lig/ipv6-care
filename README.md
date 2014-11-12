
IPv6 care - IPv6 compliance toolbox
===================================

IPv6 CARE, "IPv6 Compliant Automatic Runtime Environment", provides an environment where applications
instantly become IPv6-compliant ('patch' mode, see RFC6535).
It can also generate a diagnosis about the IPv6 compliance of an application ('check' mode).
It uses an LD_PRELOAD-based library injection technique.

Docomentation
=============
Check the [User Guide](http://sourceforge.net/project/showfiles.php?group_id=246941&package_id=301497).

Once installed you can also check the man page:
```
man ipv6_care
```

Installation steps from archive:
================================
Download the archive from [here](https://sourceforge.net/projects/ipv6-care/files/latest/download?source=files).

Then:
```
tar xfz ipv6_care-*.tar.gz
cd ipv6_care-*
./configure
make
make check # optionally
sudo make install
```

Installation steps when using github (developer):
=================================================
Fork [this github project](https://github.com/drakkar-lig/ipv6-care).

Then:
```
git clone https://github.com/<yourself>/ipv6-care
cd ipv6-care
scripts/getsourceinfo.sh
autoreconf -i
./configure
make
make check # optionally
sudo make install
```

Do not hesitate to propose enhancements or bugfixes using github pull requests. Thanks!

Main usages:
============
```
ipv6-care check <your_program_and_arguments> # assess IPv6 compliance of your program
```
```
ipv6-care patch <your_program_and_arguments> # patch your program to make it compliant
```

