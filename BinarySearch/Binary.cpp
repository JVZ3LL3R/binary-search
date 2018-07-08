// Program to test the binary search in a file
// FATEC - MC - JCB - 19/10/2017 - Versão 0.0

#include "Binary.h"

//
// Entry point of program
//
void main(void)
{
	PRODUTO stProduto,														// To receive data of one product
		vetProdutos[QTDE_PRODUTOS];											// Array of product in memory
	FILE *fdCadastro;														// File Descriptor
	char cWork[200],														// For the sprintf_s
		cOpcao;																// Rceive operator selection
	int i, j;																// Indexes and counters
	bool flgHouveTroca;														// For the Bubble Sort
	int nAuxiliar;															// For the bubble sort

	BRASIL;																	// For brazilian grammar

	// To generate a random product file
	srand(SEMENTE_RANDOM);													// Random seed

	// Loop to Generate each product record
	for (i = 0; i < QTDE_PRODUTOS; i++)
	{
		vetProdutos[i].nCodigo = rand();									// Ramdom number from 0 to 32k
		if (vetProdutos[i].nCodigo == 0)									// Do not acept zero as a key?
			vetProdutos[i].nCodigo = 1;										// Change the key to one

	// Verify if a key is already used
		for (j = 0; j < i; j++)
		{
			if (vetProdutos[j].nCodigo == vetProdutos[i].nCodigo)			// Same key?
			{
				i--;														// This key is not alowed
				break;														// Go out of this for
			} // For j
			if (j != i)														// Got the same random?
				continue;
		} // For j
		sprintf_s(vetProdutos[i].cDescricao,
			sizeof(stProduto.cDescricao),
			"Product of key: %8d", vetProdutos[i].nCodigo);
		vetProdutos[i].dPrecoUnit = rand() * 0.3458;						// Random unit price
	} // For i
	cout << "Success!" << endl;
	
	// Bouble sort to order the product vetor
	do
	{
		for (i = 0, flgHouveTroca = true; i < QTDE_PRODUTOS - 1; i++)
		{
			if (vetProdutos[i + 1].nCodigo > vetProdutos[i].nCodigo)
			{
				nAuxiliar = vetProdutos[i].nCodigo;
				vetProdutos[i].nCodigo = vetProdutos[i + 1].nCodigo;
				vetProdutos[i + 1].nCodigo = nAuxiliar;
				flgHouveTroca = true;										// Indicates chang
			}
		}
	} while (flgHouveTroca);
	PAUSA;
} // main