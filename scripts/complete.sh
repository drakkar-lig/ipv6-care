#!/bin/bash

# features supported by bash 2.05 and higher
if [ ${BASH_VERSINFO[0]} -eq 2 ] && [[ ${BASH_VERSINFO[1]} > 04 ]] ||
	   [ ${BASH_VERSINFO[0]} -gt 2 ]
then
	filenames="-o filenames"
fi

remove_prefix()
{
	num_removed_words=0
	old_length="${#COMP_LINE}"
	COMP_LINE="${COMP_LINE#ipv6_care[[:space:]]*}"
	COMP_LINE="${COMP_LINE#check[[:space:]]*}"
	COMP_LINE="${COMP_LINE#shell[[:space:]]*}"
	num_removed_words=$((num_removed_words +2))
	if [ "${COMP_WORDS[num_removed_words]}" = "-o" -a $COMP_CWORD -gt $num_removed_words ]
	then
		COMP_LINE="${COMP_LINE#-o[[:space:]]*}"
		num_removed_words=$((num_removed_words +1))
	fi
	if [ "${COMP_WORDS[num_removed_words]}" = "-v" -a $COMP_CWORD -gt $num_removed_words ]
	then
		COMP_LINE="${COMP_LINE#-v[[:space:]]*}"
		num_removed_words=$((num_removed_words +1))
	fi
	new_length="${#COMP_LINE}"
	COMP_POINT=$(( COMP_POINT + new_length - old_length ))
	old_comp_cword=$COMP_CWORD
	COMP_CWORD=$(( COMP_CWORD - num_removed_words ))

	for (( i=0; i <= $old_comp_cword; ++i ))
	do
		if [ $i -le $COMP_CWORD ]
		then
			#echo "moved COMP_WORDS[$((i+num_removed_words))] to COMP_WORDS[$i]"
			COMP_WORDS[i]="${COMP_WORDS[i+$num_removed_words]}"
		else
			#echo "remove COMP_WORDS[$i]"
			unset COMP_WORDS[i]
		fi
	done
}

complete_following_command()
{
	cur="${COMP_WORDS[COMP_CWORD]}"
	#echo
	#echo "COMP_LINE=$COMP_LINE"
	#echo "COMP_CWORD=$COMP_CWORD"
	#echo "cur=$cur"
	#echo
	remove_prefix
	cur="${COMP_WORDS[COMP_CWORD]}"
	#echo
	#echo "COMP_LINE=$COMP_LINE"
	#echo "COMP_CWORD=$COMP_CWORD"
	#echo "cur=$cur"
	#echo
	if [ $COMP_CWORD -eq 0 ]
	then
		COMPREPLY=( $(compgen -c -- "$cur") )
	else 
		if complete -p "${COMP_WORDS[0]}" &>/dev/null
		then
			cspec=$( complete -p "${COMP_WORDS[0]}" )
			if [ "${cspec#* -F }" != "$cspec" ]
			then
				func=${cspec#*-F }
				func=${func%% *}
				#echo $func $COMP_LINE
				$func "${COMP_LINE#${COMP_WORDS[0]}[[:space:]]*}"
			else
				if [ -n "$cspec" ]
				then
					cspec=${cspec#complete};
					cspec=${cspec%%$cmd};
					COMPREPLY=( $( eval compgen "$cspec" -- "$cur" ) )
				fi
			fi
		fi
	fi
	#echo "$COMP_CWORD, ${#COMPREPLY[@]}, $COMP_LINE"
	[ ${#COMPREPLY[@]} -eq 0 ] && COMPREPLY=( $( eval compgen -f -- "$cur" ) )
	#[ ${#COMPREPLY[@]} -eq 0 ] && _filedir
}

complete_ipv6_care()
{
	cur="${COMP_WORDS[COMP_CWORD]}"
	
	if [ $COMP_CWORD = "1" ]
	then
		COMPREPLY=( $(compgen -W "check shell" -- "$cur") );
	else
		MAIN_OPTION="${COMP_WORDS[1]}"

		case "$MAIN_OPTION" in
			"check")
				if [ $COMP_CWORD -gt 2 ]
				then
					#echo
					#echo "complete WITHOUT option -v"
					complete_following_command
				else
					#echo
					#echo "complete WITH option -v"
					COMPREPLY_POSSIBLE_OPTION=$(compgen -W "-v" -- ${COMP_WORDS[2]})
					complete_following_command
					COMPREPLY=( ${COMPREPLY_POSSIBLE_OPTION[@]} ${COMPREPLY[@]})
				fi
				;;
			"shell")
				#echo
				#echo "COMP_LINE=$COMP_LINE"
				#echo "COMP_CWORD=$COMP_CWORD"
				#echo "cur=$cur"
				#echo
				if [ "${COMP_WORDS[2]}" = "-o" -a "${COMP_WORDS[3]}" = "-v" -a $COMP_CWORD -gt 3 ] 
				then
					COMPREPLY=()
				else
					if [ "${COMP_WORDS[2]}" = "-o" -a $COMP_CWORD -gt 2 ] 
					then
						if [ $COMP_CWORD -gt 3 ]
						then
							COMPREPLY=()
						else
							COMPREPLY=( $(compgen -W "-v" -- "$cur") );
						fi
					else
						if [ "${COMP_WORDS[2]}" = "-v" -a $COMP_CWORD -gt 2 ] 
						then
							COMPREPLY=()
						else
							if [ $COMP_CWORD -gt 2 ]
							then
								COMPREPLY=()
							else
								COMPREPLY=( $(compgen -W "-o -v" -- "$cur") );
							fi
						fi
					fi
				fi
				;;
		esac
	fi
}
export complete_ipv6_care
complete -F complete_ipv6_care $filenames ipv6_care
