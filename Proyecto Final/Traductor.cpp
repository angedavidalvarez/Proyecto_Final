#include <iostream>
#include <string.h>
#include "Auxliar.cpp"
using namespace std;

//const char *palabrastxt = "palabras.txt";

struct palabra{
	char nombre[50];
	char traduccion[50];
	char significado[150];
};

palabra pal;

//Variables que ayudaran a no modificar un campo en especifico
string nombre_tem, traduccion_tem, significado_tem;

//Variable de improvisto para eliminar :v
int borra_ese;

void crear_archivo(){
	FILE *archivo = fopen(palabrastxt, "r+b");
	if (!archivo){
		archivo = fopen(palabrastxt,"w+b");	
	}
}

void leer(int buscar){
	//Si buscar es igual a "1" la función buscara un item; Si buscar es distinto a "1" mostrara todos los items
	FILE *archivo = fopen(palabrastxt, "rb");
	//palabra pal;
	
	int id=1, bus;
	string kam;
	
	fread(&pal,sizeof(palabra),1,archivo);
	if(buscar == 1){
		cout<<"Ingrese el ID del objeto a buscar: ";
		cin>>bus;
		cout<<"\n\n";
	}

	do{	
		if(buscar == 1 && id == bus || buscar == 0){
			kam = pal.nombre;
			if(kam != "--"){
				cout<<"ID: "<<id<<"\nNombre: "<<pal.nombre<<"\nTraduccion: "<<pal.traduccion<<"\nSignificado: "<<pal.significado<<endl<<endl;
			}
		}
		fread(&pal,sizeof(palabra),1,archivo);
		id += 1;
	}while(feof(archivo)==0);
	
	fclose(archivo);
}

//Guarda los valores a remplazar en una variable
void ayuda_remplazar(int help){
	FILE *archivo = fopen(palabrastxt, "rb");
	//palabra pal;
	int id = 1;
	fread(&pal,sizeof(palabra),1,archivo);
	do{	
		if(id == help){
			nombre_tem = pal.nombre;
			traduccion_tem = pal.traduccion;
			significado_tem = pal.significado;
		}
		fread(&pal,sizeof(palabra),1,archivo);
		id += 1;
	}while(feof(archivo)==0);
}


void ingreso(int cremo){
	//Si cremo es igual a "1" la función agregara valores; Si cremo es distingo a "1" la función modificara valores
	//palabra pal;
	FILE* archivo = fopen(palabrastxt,"ab");	
	string str_nombre, str_traduccion, str_significado;

	fflush(stdin);
	if (cremo == 1){
		cout<<"-----------------------------------Ingreso de valores-----------------------------------"<<endl<<endl;
	}else{
		fclose(archivo);
		FILE* archivo = fopen(palabrastxt,"r+b");
		int id;
		//Si no se quiere modificar un campo colocar "0"
		cout<<"Ingrese el ID que desea Modificar: "<<endl;
		cin>>id;
		fseek(archivo,(id-1) * sizeof(palabra),SEEK_SET);
		ayuda_remplazar(id);
		cin.ignore();
	}
	
	//Si es verdadero se "borrara"
	if(borra_ese == 1){
		strcpy(pal.nombre, "--");
		strcpy(pal.traduccion, "--");
		strcpy(pal.significado, "--");
	}else{	
		
		//Si no es necesario remplazar un valor en especifico se ingresa 0; Al ingresar 0, este valor se remplaza por la variable temporal (Vease ayuda_remplazar()). 
		cout<<"Ingrese el nombre:"<<endl;
		getline(cin,str_nombre);
		if(str_nombre == "0"){
			strcpy(pal.nombre, nombre_tem.c_str());
		}else{
			strcpy(pal.nombre, str_nombre.c_str());
		}
		
		cout<<"Ingrese la traduccion:"<<endl;
		getline(cin,str_traduccion);
		if(str_traduccion == "0"){
			strcpy(pal.traduccion, traduccion_tem.c_str());
		}else{
			strcpy(pal.traduccion, str_traduccion.c_str());
		}
		
		
		cout<<"Ingrese el significado:"<<endl;
		getline(cin,str_significado);
		if(str_significado == "0"){
			strcpy(pal.significado, significado_tem.c_str());
		}else{
			strcpy(pal.significado, str_significado.c_str());
		}
		//cin.ignore();
		
		//leer(0);
	}
	fwrite(&pal,sizeof(palabra),1,archivo);
	fclose(archivo);
}

void bannermotd(){
	cout<<"                 Universidad Mariano Galvez De Guatemala          "<<endl;
	cout<<"                          Facultad De Ingenieria                  "<<endl;
	cout<<"                              Proyecto final                      "<<endl<<endl;
} 


void menu(){
	int inp_gen;
	char inp_dicc;
		
	do{
		bannermotd();
		cout<<" ---------------------------------MENU-------------------------------------- "<<endl;
		cout<<endl;
		cout<<"                             Mostrar palabras                            1"<<endl;
		cout<<"                           Modificar registros                           2"<<endl;
		cout<<"                             Traducir codigo                             3"<<endl;
		cout<<"                                  Salir                                  4"<<endl;
		cout<<endl;
		cout<<" --------------------------------------------------------------------------- "<<endl<<endl;
		cout<<"Que deseas hacer? "<<endl;
		cin>>inp_gen;
		system("cls");
		switch (inp_gen){
			case 1:{
				cout<<"|----------------------------Mostrar Palabras-----------------------------|\n\n"<<endl;
				cout<<"Desea mostrar todas las palabras o buscar algo una especifico (t/e)? "<<endl;
				cin>>inp_dicc;
				if(inp_dicc == 't' || inp_dicc == 'T'){
					leer(0);
				}else if(inp_dicc == 'e' || inp_dicc == 'E'){
					leer(1);
				}else{
					cout<<"Ingresa un valor correcto la proxima vez."<<endl;
				}
				break;
			}
			case 2:{
				borra_ese = 0;
				cout<<"|--------------------------Modificar diccionario--------------------------|\n\n"<<endl;
				cout<<"Desea agregar, modificar o eliminar (a/m/e)?"<<endl;
				cin>>inp_dicc;
				if(inp_dicc == 'a' || inp_dicc == 'A'){
					system("cls");
					ingreso(1);
				}else if(inp_dicc == 'm' || inp_dicc == 'M'){
					system("cls");
					ingreso(0);
				}else if(inp_dicc == 'e' || inp_dicc == 'E'){
					system("cls");
					borra_ese = 1;
					ingreso(0);
				}else{
					cout<<"Ingresa un valor correcto la proxima vez."<<endl;
				}
				break;
			}
			case 3:{
				ingreso_del_texto();
				break;
			}
		}
		system("pause");
		system("cls");
	}while(inp_gen !=4);
}

int main(){
	crear_archivo();
	menu();

}

