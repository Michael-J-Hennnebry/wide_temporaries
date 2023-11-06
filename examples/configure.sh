# copyright Michael J. Hennebry

echo $0
SRC=$(dirname $0 )
echo SRC=${SRC} >makefile
echo include ${SRC}/example.mk >>makefile
