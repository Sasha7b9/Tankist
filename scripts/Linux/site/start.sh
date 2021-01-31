kill -9 $(pidof uwsgi)
/etc/init.d/nginx stop
cd ../../../Tankist/site/Tankist/Tankist
python3 manage.py collectstatic
uwsgi --socket :8001 --wsgi-file Tankist/wsgi.py&
/etc/init.d/nginx start
