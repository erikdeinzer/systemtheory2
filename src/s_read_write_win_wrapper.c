
/*
 * Include Files
 *
 */
#include "simstruc.h"



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <windows.h>
#include <stdio.h>

#define    BUFFERLENGTH 6


	HANDLE hComm;
	DWORD MORO;
	char   *pcCommPort = "COM3";            //Please change COM port number accordingly
	BOOL Write_Status;
    BOOL Status;
	DCB dcbSerialParams;					// Initializing DCB structure
	COMMTIMEOUTS timeouts = { 0 };
	BOOL  Read_Status;                      // Status of the various operations 
	DWORD dwEventMask;						// Event mask to trigger
	unsigned char  SerialBuffer[BUFFERLENGTH];               // Buffer Containing Rxed Data
	DWORD NoBytesRead;                     // Bytes read by ReadFile()
	int i = 0;

	DWORD  NumWritten;
	DWORD  dNoOFBytestoWrite = 4;              // No of bytes to write into the port
	DWORD  dNoOfBytesWritten = 0;          // No of bytes written to the port
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define y_width 3

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start function
 *
 */
void s_read_write_win_Start_wrapper(real_T *xD,
			SimStruct *S)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
hComm = CreateFileA(pcCommPort,
		GENERIC_READ | GENERIC_WRITE,
		0,    // must be opened with exclusive-access
		NULL, // no security attributes
		OPEN_EXISTING, // must use OPEN_EXISTING
		0,    // not overlapped I/O
		NULL  // hTemplate must be NULL for comm devices
	);

	if (hComm == INVALID_HANDLE_VALUE)
	{
		
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			ssSetErrorStatus(S,"Cannot open Port");
			return;
		}

		ssSetErrorStatus(S,"Invalid handle value");
		return;
	}
	else {
	  //printf("opening serial port successful");
	}

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	Write_Status = GetCommState(hComm, &dcbSerialParams);     //retreives  the current settings

	if (Write_Status == FALSE) {
		//printf("\n   Error! in GetCommState()");
		CloseHandle(hComm);
		ssSetErrorStatus(S,"Error! in GetCommState()");
		
	}


	dcbSerialParams.BaudRate = 2000000;    //  Setting BaudRate = 2000000
	dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
											  //dcbSerialParams.
	dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
	dcbSerialParams.Parity = NOPARITY;      // Setting Parity = None

	Write_Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB

	if (Write_Status == FALSE)
	{
		//printf("\n   Error! in Setting DCB Structure");
		CloseHandle(hComm);
		ssSetErrorStatus(S,"Error! in Setting DCB Structure");
		
	}
	else
	{
		//printf("\n   Setting DCB Structure Successful\n");
		//printf("\n       Baudrate = %d", dcbSerialParams.BaudRate);
		//printf("\n       ByteSize = %d", dcbSerialParams.ByteSize);
		//printf("\n       StopBits = %d", dcbSerialParams.StopBits);
		//printf("\n       Parity   = %d", dcbSerialParams.Parity);
	}

	// Set COM port timeout settings in milliseconds
	timeouts.ReadIntervalTimeout = 5;
	timeouts.ReadTotalTimeoutConstant = 5;
	timeouts.ReadTotalTimeoutMultiplier = 1;
	timeouts.WriteTotalTimeoutConstant = 5;
	timeouts.WriteTotalTimeoutMultiplier = 1;
	if (SetCommTimeouts(hComm, &timeouts) == 0)
	{
		//printf("Error setting timeouts\n");
		CloseHandle(hComm);
		ssSetErrorStatus(S,"Error setting timeouts");
		//return 1;
	}
       //Set read event
  	Read_Status = SetCommMask(hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception
	if (Read_Status == FALSE) {
		ssSetErrorStatus(S,"Error! in Setting CommMask");
    }
    //Toggle DTR line to auto-reset arduino.
    Status = EscapeCommFunction(hComm, CLRDTR);
    Sleep(10);
    Status = EscapeCommFunction(hComm, SETDTR);
    PurgeComm(hComm, PURGE_RXCLEAR);
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void s_read_write_win_Outputs_wrapper(const int32_T *TX,
			int16_T *RX,
			const real_T *xD,
			SimStruct *S)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/*----------------------------- Writing a Character to Serial Port----------------------------------------*/

 

	if (!WriteFile(hComm, (unsigned char *)&TX[0], dNoOFBytestoWrite,
		&dNoOfBytesWritten, NULL))
	{
		//printf("Error writing text to %s\n", pcCommPort);
	}   
    


    
    /*------------------------------------ Reading from Serial Port ----------------------------------------------*/
	Read_Status = WaitCommEvent(hComm, &dwEventMask, NULL); //Wait for the character to be received
	if (Read_Status == FALSE){
		//ssSetErrorStatus(S,"Error! in Setting WaitCommEvent()");
        ssSetErrorStatus(S,"Serial port disconnected");
        PurgeComm(hComm, PURGE_RXCLEAR);
    }
    else{
    if (!ReadFile(hComm, SerialBuffer, BUFFERLENGTH, &NoBytesRead, NULL))
			{
				ssSetErrorStatus(S,"Serial port disconnected");
			}
   
       
  
     //RX[3]= (SerialBuffer[7]<<8)|(SerialBuffer[6]); 
     RX[1]= (SerialBuffer[3]<<8)|(SerialBuffer[2]);
     RX[2]= (SerialBuffer[5]<<8)|(SerialBuffer[4]);
     RX[0]= (SerialBuffer[1]<<8)|(SerialBuffer[0]);
    
    // PurgeComm(hComm, PURGE_RXCLEAR);
    }
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Updates function
 *
 */
void s_read_write_win_Update_wrapper(const int32_T *TX,
			int16_T *RX,
			real_T *xD,
			SimStruct *S)
{
/* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
/*
 * Code example
 *   xD[0] = u0[0];
 */
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Terminate function
 *
 */
void s_read_write_win_Terminate_wrapper(real_T *xD,
			SimStruct *S)
{
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_BEGIN --- EDIT HERE TO _END */
CloseHandle(hComm);//Closing the Serial Port
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_END --- EDIT HERE TO _BEGIN */
}

