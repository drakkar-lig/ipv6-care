#!/bin/bash
SCRIPTS_DIR=$(cd $(dirname $0); pwd)
MAN_DIR=$SCRIPTS_DIR/../man
MAN_PAGE=$MAN_DIR/ipv6_care.8
EXTERNAL_MAN_HOST=linux.die.net

man2html -H $EXTERNAL_MAN_HOST -M "/man" -p $MAN_PAGE | \
	sed 	-e 's/\(man\/.\)+/\1\//g' \
		-e 's/man"/man\/1\/man2html"/g' \
	       	-e 's/<A HREF="#index".*A>//g' \
		-e 's/<A HREF=.*Main Contents..A>//g' \
		-e 's/<A HREF="mailto:\(.*\)".*A>/\1/g'	| \
	html2wiki --dialect MediaWiki | \
	awk 	'
						{ do_print = 1 }
		/==Index==/,/----/ 		{ do_print = 0 }
		/Content-type.*/,/=ipv6_care=/ 	{ do_print = 0 }
						{ if (do_print == 1) print }
		'
echo 
echo __NOEDITSECTION__
