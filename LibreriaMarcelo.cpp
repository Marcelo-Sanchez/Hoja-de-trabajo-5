#include <fstream>
#include <iostream>
#include <string>
#include <sstream> 
#include <regex>
#include <iomanip> 

using namespace std;
void insert_data_db();
void mp();
void leer_data_db();
void eliminar();
void modificar();


int main(){	
	mp();
	
}
void mp(){
	int resp;
	
	
	do {
		system("CLS");
		cout<<"--------------------------"<<"\n";
		cout<<" Menu Principal de la LIBRERIA"<<"\n";
		cout<<"-------------------"<<"\n";
		cout<<" 1 - Ingresar datos sobre la libreria "<<"\n";
		cout<<" 2 - Reporte "<<"\n";
		cout<<" 3 - Eliminar Registro"<<"\n";
		cout<<" 4 - Modificar Registro"<<"\n";
		cout<<" 5 - Salir"<<"\n";
		cout<<"--------------------------"<<"\n";
		cout<<" Seleccione su opcion: ";
		cin>>resp;
		if (resp==1){		
			system("CLS");
			insert_data_db();			
		}
		else if (resp==2){		
			system("CLS");
			leer_data_db();
		}
		else if (resp==3){		
			system("CLS");
			eliminar();	
		}			
		else if (resp==4){
			system("CLS");
			modificar();
		}
		else if (resp==5)
			break;
		else 
			break;
		
	} while(resp!=5);	
}


void insert_data_db(){
	//declaracion de variables
	int diai;
	int mod;
	int cant;
	float precio, tot;
	ofstream db;

	system("CLS");
	//Ingreso de datos
	cout<<"*** Ingreso de Datos de la libreria ***\n\n";
	cout<<"Indique el dia de la venta: "<<endl;
	cin>>diai;
	//cin.ignore();
	fflush(stdin);
	cout<<"Indique el modelo del cuaderno: (1-4)     "<<endl;
	cin>>mod;
	fflush(stdin);	
	cout<<"Indique la cantidad del cuaderno:         "<<endl;
	cin>>cant;
		if (mod == 1){
			precio = 10.00;
			tot = precio*cant;
		}
		else if (mod == 2){
			precio = 15.00;
			tot = precio*cant;
		}
		else if (mod == 3){
			precio = 18.50;
			tot = precio*cant;
		}
		else if (mod == 4){
			precio = 25.00;
			tot = precio*cant;
		}
	
	
	//Insercion de datos a un archivo
	try {
		db.open("Libreria.txt",ios::app);
		db<<"\t"<<diai<<"\t"<<mod<<"\t"<<cant<<endl;   //"|"
		db.close();
	}
	catch(exception X){
		cout<<"Error en la manipulacion del archivo"<<endl;
		system("Pause");
	}	
}
void leer_data_db(){
	//declaracion de variables
	int i, mayorm;
	float diai,mod,cant;
	float to=0;
	float m1=0;
	float m2=0;
	float m3=0;
	float m4=0;
	string linea;
	float suma= 0;
	int mayortot = -1;


	
	ifstream db;	
	try{
		db.open("Libreria.txt",ios::in);	

		cout<<"Datos del archivo:"<<endl;
		cout<<"| DIA  |"<<"MODELO|"<<"CANTIDAD|"<<"TOTAL Q.|"<<endl;		
		while (db>>diai>>mod>>cant){
			//reemplaca "_" con " "	<-espacios en blanco
			const auto obj = regex{ "_" };
    		const auto repl = string{ " " };
    		const auto valor = mod;
			//
			cout<<setw(3)<<diai<<"|"<<setw(4)<<mod<<setw(3)<<cant<<"|"<<endl;				
			if (mod==1){
				m1+=to;
			}
			else if (mod==2){
				m2+=to;
			}
			else if (mod==3){
				m3+=to;
			}
			else if (mod==4){
				m4+=to;
			}
			
			if (mod>mayortot){
				mayortot=mod;
				mayorm=mod;
			}
			
		}	
		db.close();	
		
		cout<<"\n_______MODELOS VENDIDOS_______"<<endl<<endl;
		cout<<setprecision(5)<<" MODELO #1  "<<m1<<endl;
		cout<<setprecision(5)<<" MODELO #2  "<<m2<<endl;
		cout<<setprecision(5)<<" MODELO #3  "<<m3<<endl;
		cout<<setprecision(5)<<" MODELO #4  "<<m4<<endl;
		cout<<"EL MODELO MAS VENDIDO FUE EL MODELO #"<<mayorm<<endl<<endl;
		system("Pause");
	}
	catch(exception& X){
		cout<<"Error en la manipulacion del archivo"<<endl;
		cout<<"Error: "<<X.what()<<endl;
		system("Pause");
	}
	
}


void eliminar(){
	ifstream db_a; //archivo anterior
	ofstream db_n; //archivo nuevo
	int aux,diai,mod,cant,flag;
	remove("Temporal.txt");
	
	db_a.open("Libreria.txt",ios::in);
	db_n.open("Temporal.txt",ios::app);
	
	cout<<"Ingrese Dia  que desea borrar: "<<endl;
	cin>>aux;
	
	while (db_a>>diai>>mod>>cant){
		if(aux==diai){
			cout<<"Registro Eliminado...."<<endl;
			flag =1;
		}			
		else if(aux!=diai)
			db_n<<diai<<"\t"<<mod<<"\t"<<cant<<endl;
		//aux=0;
		//oid=0;					
	}
	db_a.close();
	db_n.close();
	
	if (flag==1){
		remove("Libreria.txt");
		rename("Temporal.txt","Libreria.txt");
	}	
	system("Pause");
}

void modificar(){
	ifstream db_a; //archivo anterior
	ofstream db_n; //archivo nuevo
	int aux,diai,mod,flag,cant;
	char respuesta;
	remove("Temporal.txt");
	
	db_a.open("Libreria.txt",ios::in);
	db_n.open("Temporal.txt",ios::app);
	
	cout<<"Ingrese Dia al que modificara informacion: "<<endl;
	cin>>aux;
	do {
		cout<<"Ingrese modelo a modificar: "<<endl;
		cin>>mod;
		cout<<"Ingrese cantidad a modificar: "<<endl;
		cin>>cant;
		cout<<"\n\nEsta Seguro? S/N";
		cin>>respuesta;
		cout<<"\n"<<endl;
		respuesta = toupper(respuesta);		
	} while (respuesta!='S');	
	
	//leer archivo anterior
	while (db_a>>diai>>mod>>cant){
		if(aux==diai){
			db_n<<diai<<"\t"<<mod<<"\t"<<cant<<endl;
			cout<<"Archivo Actualizado...."<<endl;
			flag =1;
		}			
		else if(aux!=diai)
			db_n<<diai<<"\t"<<mod<<"\t"<<cant<<endl;
		//aux=0;
		//oid=0;					
	}
	db_a.close();
	db_n.close();
	
	if (flag==1){
		remove("Libreria.txt");
		rename("Temporal.txt","Libreria.txt");
	}	
	system("Pause");
}
