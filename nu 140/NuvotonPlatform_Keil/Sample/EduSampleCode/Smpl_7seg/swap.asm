		        PRESERVE8 ; Indicate the code here preserve  
; 8 byte stack alignment         
                     THUMB     ; Indicate THUMB code is used       
                 AREA    |.text|, CODE, READONLY
			   
              EXPORT _main			 
; Start of CODE area 
_main 	
			LDR	R0,=0XF631024C
			LDR	R1,=0X17539ABD
			EORS	R0,R0,R1			;R0^R1
			EORS	R1,R0,R1			;R1^R0
			EORS	R0,R0,R1			;R0^R1

stop	      B	   stop		 		;stop program
	          END	
	   	