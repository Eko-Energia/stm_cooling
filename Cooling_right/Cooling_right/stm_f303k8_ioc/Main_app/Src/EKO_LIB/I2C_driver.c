///*
// * I2C_driver.c
// *
// *  Created on: Dec 12, 2025
// *      Author: Karol
// */
//#include "I2C_driver.h"
//
///*
// *
// * ARGS:
//	 * Tx_frame - struktura z informacją o ramce głównej
// * RETURN:
// 	 * HAL_OK - pomyślnie wykonano operacje
// 	 * HAL_ERROR - wystąpił błąd -> wywołąnie asser_failed()
// *
// */
//HAL_StatusTypeDef I2C_Transmit_message(struct I2C_frame* Tx_frame) // Funkcja do wysyłki danych po I2C
//{
//	if (Tx_frame->addres <= 0x7F)							// Adres wraz z bitem Write/Read ma dokładnie 8 bitów
//	{
//		// ERROR HANDLER
//		return HAL_ERROR;
//	}
//
//	if (HAL_I2C_Master_Transmit(Tx_frame->hi2c, Tx_frame->addres, Tx_frame->data , Tx_frame->size_data, Tx_frame->timeout) != HAL_OK )
//	{
//		// ERROR HANDLER
//		return HAL_ERROR;					// Ramka główna
//	}
//
//	return HAL_OK;
//}
//
//
//// FUNKCJA MA BYĆ UŻYTA W TIMER KTÓRY BĘDZIE WYWOŁYWANY CO OKRES MIEDZY RAMKAMKI NP. DLA AM2320 TO 1MS.
///*
// *
// * ARGS:
//	 * Rx_frame - struktura z informacją o ramce głównej
// * RETURN:
// 	 * HAL_OK - pomyślnie wykonano operacje
// 	 * HAL_ERROR - wystąpił błąd -> wywołanie asser_failed()
// *
// */
//HAL_StatusTypeDef I2C_Receive_message(struct I2C_frame* Rx_frame)
//{
//	if (Rx_frame->addres <= 0x7F)// adres wraz z bitem Write/Read ma dokładnie 8 bitów
//	{
//		// ERROR HANDLER
//		return HAL_ERROR;
//	}
//
//	if (HAL_I2C_Master_Receive(Rx_frame->hi2c, Rx_frame->addres, Rx_frame->data, Rx_frame->size_data, Rx_frame->timeout) != HAL_OK )
//	{
//		// ERROR HANDLER
//		return HAL_ERROR;										// Ramka główna
//	}
//	return HAL_OK;
//}
//
//// FUNCKJA SPRAWDZAJĄCA CZY ADRESY RAMEK SĄ W ZAKRESIE <128, 255>
///*
// *
// * ARGS:
//	 * Frames - Tablica adresów
// * RETURN:
// 	 * HAL_OK - Ramki nie zawierają błędów
// 	 * HAL_ERROR - Ramki zawierają błąd
// *
// */
//HAL_StatusTypeDef I2C_Valid_address(uint8_t* Frames, uint8_t Size)
//{
//	uint8_t bit_map[16] = {0}; // 16*8 = 128
//	uint8_t byte = 0;
//	uint8_t bit = 0;
//	int16_t address = 0;
//
//	for(uint8_t i = 0; i < Size; i++){
//		address = Frames[i] - 128; // przesuwam adres do zakresu <0,127>
//
//		byte = address / 8;		// sprawdzam na którym ideksie czyli bajcie w tablicy bit_map wylonduje adres
//		bit  = address % 8;		// określa na którym miejscu w ciągu 00000000 jest jedynka.
//
//		if ( address < 0 || byte >= 16|| bit_map[byte] & (1 << bit)) { 	// jeśli wartość adresu z struktury była mniejsza niż 128 to wyłapie to address<0
//																		// jeśli wartość adresu z struktury ponad 255
//																		// sprawdzam czy w bit_map nie ma już takiej liczby
//			return HAL_ERROR;		// ADRESY SIĘ POWAŻAJĄ
//		}
//
//		bit_map[byte] |= (1 << bit);	// zapisuje w bit map liczbę wynikową z operacji: map_bit[byte] OR np.(00010000) miejsce jedynki zależne od zmiennej bit,
//	}
//	return HAL_OK; // adresy POPRAWNE
//}
