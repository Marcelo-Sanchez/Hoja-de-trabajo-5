#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <iomanip>      
#include <vector>

using namespace std;

struct personas{
  float peso;
  float altura;
  int edad;
  string genero;
};

void ordenamiento(){
  
  personas temp;
  vector<personas> registros;

  // leer archivo
  ifstream db_read;
  db_read.open("registros.txt",ios::in);
	
  while(db_read>>temp.peso>>temp.altura>>temp.edad>>temp.genero){

    registros.push_back(temp);
  };

  db_read.close();
    
  //Ordenamiento de BUBBLESORT por edad
  for(int i=0; i<registros.size(); i++) {
   for(int j=i+1; j<registros.size(); j++)
   {
      // se compara por edad
      if(registros[j].edad < registros[i].edad) {
         temp = registros[i];
         registros[i] = registros[j];
         registros[j] = temp;
      }
   }
  } 


    // remplazamos el archivo.
    ofstream db;
    db.open("registros.txt",ios::out);
    
    for (int i=0; i<registros.size(); i++){
      db << registros[i].peso <<"\t"<< registros[i].altura <<"\t"<< registros[i].edad <<"\t"<< registros[i].genero <<endl;
    }
    db.close();
}

void insert_data_db(){
	
  string genero;
	personas x;

 
  ofstream db;
  
	
  cout<<"Indique el peso de la persona:         "<<endl;
 	cin>>x.peso;
	cin.clear(); 
  
  cout<<"Indique la altura de la persona:         "<<endl;
	cin>>x.altura;
  cin.clear(); 
	
  cout<<"Indique la edad de la persona:         "<<endl;
	cin>>x.edad;
 
	cin.ignore();
  

  bool validacion=false;
  while (validacion==false) {
    cout<<"Indique genero de la persona (m= si es Masculino, f= si es Feminino): "<<endl;
    getline(cin,genero);    

    // comparamos
    if ((genero=="M") or (genero=="m")) {
      x.genero="M";
      validacion=true;
    } else if ((genero=="F") or (genero=="f")) {
      x.genero="F";
      validacion=true;
    } else {
      cout << "Indico una opción invalida!!! \n Vuelva a intentarlo .... \n";
    }
  }
  cin.clear(); 

	try {
		
    db.open("registros.txt",ios::app);
    
    db << x.peso <<"\t"<< x.altura <<"\t"<< x.edad <<"\t"<< x.genero <<endl;
		
    db.close();
	}

	catch(exception X){
		cout<<"Error en la manipulacion del archivo"<<endl;
		
	}
  ordenamiento();
}

void leer_data_db(){
  personas x;

  int i=0;
  float prom_peso, prom_altura, prom_edad;
	ifstream db;	
	
  try{
		db.open("registros.txt",ios::in);	
 
		cout<<"Datos del archivo:"<<endl;
		cout<<" Peso|"<<"      Altura      |"<<"  Edad|"<<"  Genero|"<<endl;		
		while (db>>x.peso>>x.altura>>x.edad>>x.genero){
			cout<<setw(5)<<x.peso<<"|"<<setw(10)<<x.altura<<setw(9)<<"|"<<setw(3)<<x.edad<<setw(4)<<"|"<<setw(4)<< x.genero<<setw(5)<<"|"<<endl;
     
      i++;					
      
 
			prom_edad+=x.edad;
      prom_altura+=x.altura;
      prom_peso+=x.peso;
		}	
		db.close();	
    
   
    prom_edad=prom_edad/i;
    prom_altura=prom_altura/i;
    prom_peso=prom_peso/i;
		
		cout<<"Promedio de Peso: "<<prom_peso<<endl;
		cout<<"Promedio de Altura: "<<prom_altura<<endl;
    cout<<"Promedio de Edad: "<<prom_edad<<endl;
    cin.ignore();
    
	}
	catch(exception& X){
		cout<<"Error en la manipulacion del archivo"<<endl;
		cout<<"Error: "<<X.what()<<endl;
	
	}
};

void mp(){
	int resp;
	do {
   
    
		cout<<"--------------------------"<<"\n";
		cout<<" Menu Principal"<<"\n";
		cout<<"-------------------"<<"\n";
		cout<<" 1 - Ingresar registro "<<"\n";
		cout<<" 2 - Reporte "<<"\n";
		cout<<" 3 - Salir"<<"\n";
		cout<<"--------------------------"<<"\n";
		cout<<" Seleccione su opcion: ";
		cin>>resp;
		if (resp==1){		
			  
			insert_data_db();			
		}
		else if (resp==2){		
      leer_data_db();
		}
		else if (resp==3)
			break;
		else 
			break;
		
	} while(resp!=3);	
}



int main(){
  mp();

return 0;
};
