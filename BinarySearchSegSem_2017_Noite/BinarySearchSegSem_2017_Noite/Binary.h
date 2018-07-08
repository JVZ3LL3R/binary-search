#pragma once
#define TESTE 1
#include <iostream>
#include <Windows.h>
using namespace std;

// Defines

#define PAUSA														system("pause")
#define LIMAPAR_TELA												system("cls")
#define BRASIL														setlocale(LC_ALL, "portuguese_brazil")

// Opções do Menu do Programa de Teste

#define MOSTRAR_PRODUTO												'M'
#define SAIR_DO_PROGRAMA											'S'

// Para geração de um arquivo de teste

#define SEMENTE_RANDOM												240
#define CAMINHO_CADASTRO											"..\\Produtos.cad" // ".cad" SO associa um programa que lê esse tipo de extensão, perguntar para o Almir qual o programa do SO que faz isso
#define QTDE_PRODUTOS												12000

//
// Struct do Registro de Produto
//
typedef struct tagPRODUTO
{
	int nCodigo;													// Código do Produto ou chave primária
	char cDescricao[41];											// Descrição do Produto
	double dPrecoUnit;												// Preço unitário
}PRODUTO;

//
// Class Binary Search
//
class clBinarySearch
{
private:
	// Private Atributes
	PRODUTO stProduto;												// Contains informations of one product
	unsigned int nQtdeAcessos,										// Maximum quantity of access in the file
		regInf,														// Lower positional
		regSup,														// Higher positional
		nQtRegistros;												// Quantity of Records in the file
	
public:
	// Public Methods

	// Constructor Method
	// Parameters:
	//		Input: nQtRegistros - Total quantity of products records
	clBinarySearch(int nQtRegistros)
	{
		unsigned int nQtdeTrab = nQtRegistros;						// Quantity of Records
		this->nQtRegistros = nQtRegistros;							// Backup of qty of records
		
		// Successive divisions by 2 - To obatain nQtdeAcessos (2^^n+1) = Qty of acess
		for (nQtdeAcessos = 1;										// Start with plus one (precaution)
			nQtdeTrab > 1;											// While qty of records greater than one
			nQtdeAcessos++)											// Increase the number of access
				nQtdeTrab >>= 1;									// Shift right bt one (divides by 2 [one binary])
#ifdef TESTE
		cout << "Total qty: " << nQtRegistros
			<< "Max qty of Access: " << nQtdeAcessos << endl;
		PAUSA;
#endif
	} // Constructor Method

	// Algorithm for the binary search
	// Parameters:
	//		Input: int nKey					- It's the key to search
	//			   PRODUTO *ptrStProduto	- Pointer to struct thats receive the product
	//										  data if it's founder
	//			   FILE *fdCadastro			- File descriptor of the FILE
	//
	//		Output: Bool - True  - The product key was found and it's data
	//							   was copied to struct of the caller
	//					   False - Product NOT FOUND	
	bool BinarySearch(int nKey, PRODUTO *ptrStProduto, FILE *fdCadastro)
	{
		unsigned int nQtdeAcessos = this->nQtdeAcessos;				// Max number of access in the file
		int regAcessar;												// Positional to access

		// Initialiize the lower and heighter positional access in the file
		regInf = 0;													// Lower positional
		regSup = nQtRegistros;										// Heighter positional

		// Loop of access to the file
		while (nQtdeAcessos)
		{
			nQtdeAcessos--;											// Minuss one access

			// To calculate the record to acces 
			regAcessar = ((regSup - regInf) / 2) + regInf;
			if (fseek(fdCadastro, regAcessar * sizeof(PRODUTO), SEEK_SET) != 0)	// Seek error?
				return false;										// Advise "Not Found"?

			// Read record that's already positioned
			if (fread_s(&stProduto, sizeof(PRODUTO), sizeof(PRODUTO), 1, fdCadastro) == 0) // Read error?
				return false;										// Advise "Not Found"?

			// The record was read
			if (nKey == stProduto.nCodigo)							// Found?
			{ // The product key was found
				memcpy_s(ptrStProduto, sizeof(PRODUTO), &stProduto, sizeof(PRODUTO));	// Copy product data to caller
				return true;										// Return advising product found
			}
			else if (nKey > stProduto.nCodigo)						// Key is greater than record key?
				regInf = regAcessar;								// Lower limit is the positional accessed
			else
				regSup = regAcessar;								// Heghter limit is the positional accessed
		} // While
		
		return false;												// Record key not found
	} // Binary Search Algorithm

	bool SalvaProdutosEmDico()
	{

	}
};
