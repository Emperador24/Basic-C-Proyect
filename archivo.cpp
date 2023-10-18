#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

struct Producto{
	int codigo;
	string nombre;
	float precio;
	int cant;
};
struct Cliente{
	char tp;
	int documento;
	string nombre;
	string direccion;
};
struct Orden{
	int n;
	int identificacion;
	string nombre;
	int cant;
	string nombreP;
	float total;
};

void agregarProducto();
void agregarCliente();
bool buscarTexto(int x, string nom);
void buscarProducto();
void buscarCliente();
void registrarCompra();
void modificarCompra();
void reporteVentas();
void ordenes();
void modificar(Orden ordenes[], int aux);
Producto * cargarProducto();
Cliente * cargarCliente();
Orden * cargarOrdenes();

int main(){
	int x, aux=0, tamP=0, tamC=0, tamO=0;
	Orden * ord;
	Producto * prod;
	Cliente * cli;
	cout<<"Bienvedido a Electrodomesticos Javeriana"<<endl;
	prod = cargarProducto();
	cli = cargarCliente();
	ord = cargarOrdenes();
	do{
		cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<MENU>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
		cout<<"1) Agregar Producto"<<endl<<"2) Agregar Cliente"<<endl<<"3) Registrar Compra"<<endl<<"4) Modificar Compra"<<endl<<"5) Buscar Producto"<<endl<<"6) Buscar Cliente"<<endl<<"7) Generar Reporte de ventas"<<endl<<"8) Imprimir ordenes"<<endl<<"9) Salir"<<endl;
		cout<<"Digite una opcion: ";
		cin>>x;
		cout<<endl<<endl;
		switch(x){
			case 1:
				agregarProducto();
				prod = cargarProducto();
				break;				
			case 2:
				agregarCliente();	
				cli = cargarCliente();			
				break;
			case 3:
				registrarCompra();
				ord = cargarOrdenes();				
				break;
			case 4:
				modificarCompra();
				ord = cargarOrdenes();
				break;
			case 5:
				buscarProducto();				
				break;				
			case 6:
				buscarCliente();
				break;
			case 7:
				reporteVentas();
				break;
			case 8:
				ordenes();
				break;
			case 9:
				exit(0);
				break;
			default:
				cout<<"Digite una opcion valida"<<endl;
				break;
		}
		
	}while(aux==0);
		
	return 0;
}


void agregarProducto(){
	ofstream producto;
	Producto productos;
	Producto *productoPtr;
	productoPtr = &productos;
	bool aux;
	string p ="producto";
	
	producto.open("productos.txt", ios::app);
	if(!producto.fail()){
		cout<<"Digite el codigo del producto"<<endl;
		cin>>productoPtr->codigo;
		aux=buscarTexto(productoPtr->codigo, p);
		if(!aux){
			cout<<"Digite el nombre del producto"<<endl;
			cin>>productoPtr->nombre;
			cout<<"Digite el precio del producto"<<endl;
			cin>>productoPtr->precio;
			cout<<"Digite la cantidad del producto"<<endl;
			cin>>productoPtr->cant;
			producto<<productoPtr->codigo<<","<<productoPtr->nombre<<","<<productoPtr->precio<<","<<productoPtr->cant<<endl;
		}else{
			cout<<"El producto con el codigo "<<productoPtr->codigo<<" ya se encuentra registrado"<<endl;
		}
	}else{
		cout<<"No se pudo abrir el archivo"<<endl;
		exit(0);
	}
	
	producto.close();
}

void agregarCliente(){
	ofstream cliente;
	Cliente *clientePtr;
	Cliente clientes;
	clientePtr = &clientes;
	bool aux;
	string nom = "cliente";
	
	cliente.open("clientes.txt", ios::app);
	if(!cliente.fail()){
		cout<<"Digite el tipo de documento del cliente(C(cedula de ciudadania), E(cedula de extranjeria))"<<endl;
		cin>>clientePtr->tp;
		cout<<"Digite el numero de documento del cliente"<<endl;
		cin>>clientePtr->documento;
		aux=buscarTexto(clientePtr->documento, nom);
		if(!aux){
			string nombre, apellido;
			cout<<"Digite el nombre del cliente"<<endl;
			cin>>nombre;
			cout<<"Digite el apellido del cliente"<<endl;
			cin>>apellido;
			nombre +=" " +apellido;
			clientePtr->nombre=nombre;
			cout<<"Digite la direccion del cliente"<<endl;
			cin>>clientePtr->direccion;
			cliente<<clientePtr->tp<<","<<clientePtr->documento<<","<<clientePtr->nombre<<","<<clientePtr->direccion<<endl;
		}else{
			cout<<"El cliente con el numero de documento "<<clientePtr->documento<<" ya se encuentra registrado"<<endl;
		}
	}else{
		cout<<"No se pudo abrir el archivo"<<endl;
		exit(0);
	}
	
	cliente.close();
}

bool buscarTexto(int x, string nom){
	string c ="cliente", p="producto";
	ifstream archivo;
	
	if(c==nom){
		archivo.open("clientes.txt", ios::in);
		while(!archivo.eof()){
			int doc;
			string nombre, direccion;
			char tp;
			archivo>>tp;
			archivo.ignore(2, ',');
			archivo>>doc;
			archivo.ignore(2, ',');
			getline(archivo, nombre, ',');
			archivo>>direccion;
			if(x==doc){
				return true;
			}
		}
		archivo.close();
	}else if(p==nom){
		archivo.open("productos.txt", ios::in);
		while(!archivo.eof()){
			int cod, cant;
			string nombre;
			float precio;
			archivo>>cod;
			archivo.ignore(2, ',');
			getline(archivo, nombre, ',');
			archivo>>precio;
			archivo.ignore(2, ',');
			archivo>>cant;
			if(x==cod){
				return true;
			}
		}
		archivo.close();
	}	
	
	return false;
}

void buscarProducto(){
	ifstream archivo;
	Producto proc;
	Producto *p;
	p=&proc;
	archivo.open("productos.txt", ios::in);
	string s;
	cout<<"Digite la cadena caracteres para buscar el producto"<<endl;
	cin>>s;
	const char *c = s.c_str();
	int len = strlen(c), cont=1;
	while(!archivo.eof()){
			archivo>>p->codigo;
			archivo.ignore(2, ',');
			getline(archivo, p->nombre, ',');
			archivo>>p->precio;
			archivo.ignore(2, ',');
			archivo>>p->cant;
			const char *aux = p->nombre.c_str();
			int comp = strncmp(c, aux, len);
			if(comp == 0){
				cout<<"PRODUCTO ENCONTRADO"<<endl;
				cout<<"Codigo: "<<p->codigo<<endl;
				cout<<"Nombre: "<<p->nombre<<endl;
				cout<<"Precio: "<<p->precio<<endl;
				cout<<"Cantidad: "<<p->cant<<endl;
				cont=1;	
			}
		}
		if(cont==0){
			cout<<"PRODUCTO NO ENCONTRADO"<<endl;
		}
		archivo.close();
}

void buscarCliente(){
	ifstream archivo;
	Cliente clientes;
	Cliente *cli;
	cli=&clientes;
	archivo.open("clientes.txt", ios::in);
	string s;
	cout<<"Digite la cadena caracteres para buscar el producto"<<endl;
	cin>>s;
	const char *c = s.c_str();
	toupper(*c);
	int len = strlen(c), cont =1;
	while(!archivo.eof()){
			archivo>>cli->tp;
			archivo.ignore(2, ',');
			archivo>>cli->documento;
			archivo.ignore(2, ',');
			getline(archivo, cli->nombre, ',');
			archivo>>cli->direccion;
			const char *aux = cli->nombre.c_str();
			int comp = strncmp(c, aux, len);
			if(comp == 0){
				cout<<"CLIENTE ENCONTRADO"<<endl;
				cout<<"Tipo de Documento:   "<<cli->tp<<endl;
				cout<<"Numero de Documento: "<<cli->documento<<endl;
				cout<<"Nombre:              "<<cli->nombre<<endl;
				cout<<"Direccion:           "<<cli->direccion<<endl;
				cont=0;	
			}
		}
		if(cont==1){
			cout<<"CLIENTE NO ENCONTRADO"<<endl;
		}
		archivo.close();
}

void registrarCompra(){
	ifstream cliente;
	ofstream salida;
	ofstream ordenBin;
	ifstream producto;
	cliente.open("clientes.txt", ios::in);
	salida.open("reporte.txt", ios::app);
	ordenBin.open("ordenes.dat", ios::binary);
	
	Cliente clientes;
	Cliente *c;
	c=&clientes;
	Producto productos;
	Producto *p;
	p=&productos;
	
	int doc;
	cout<<"Digite el numero de documento del cliente"<<endl;
	cin>>doc;
	bool aux;
	aux=buscarTexto(doc, "cliente");
	if(!aux){
		bool r, s=0;
		cout<<"Cliente no registrado"<<endl;
		while(s==0){
			cout<<"Desea regitrar al cliente? (1=si)(0=no)"<<endl;
			cin>>r;
			if(r){
				agregarCliente();
				s=1;
			}else{
				cout<<"Debes registrar al cliente para regitrar la compra"<<endl;
			}
		}
	}else if(aux){
		while(!cliente.eof()){
			char tp;
			string nombre, direccion;
			int docu;
			cliente>>tp;
			cliente.ignore(2, ',');
			cliente>>doc;
			cliente.ignore(2, ',');
			getline(cliente, nombre, ',');
			cliente>>direccion;
			if(doc==docu){
				c->tp = tp;
				c->documento = docu;
				c->nombre = nombre;
				c->direccion = direccion;
			}
		}
	}
	Orden ord;
	Orden *o;
	o=&ord;
	cout<<"Digite el numero de orden de compra"<<endl;
	cin>>o->n;
	o->nombre= c->nombre;
	o->identificacion= c->documento;	

	int w=5;
	do{
		int cod;
		bool b;
		cout<<"Digite el codigo del producto a facturar"<<endl;
		cin>>cod;
		b=buscarTexto(cod, "producto");
		if(b){
			producto.open("productos.txt", ios::in);
			while(!producto.eof()){
				string nombre;
				int codigo, cant;
				float precio;
				producto>>codigo;
				producto.ignore(2, ',');
				getline(producto, nombre, ',');
				producto>>precio;
				producto.ignore(2, ',');
				producto>>cant;
				if(cod==codigo){
					p->codigo = codigo;
					p->nombre = nombre;
					p->precio = precio;
					p->cant = cant;
					cout<<p->codigo<<" "<<p->nombre<<" "<<p->cant<<" "<<p->precio<<endl;
				}
			}
			int cp, seguro, total; 
			cout<<"Digite la cantidad de productos a comprar (la cantidad disponible del producto es: "<<p->cant<<" )"<<endl;
			cin>>cp;
			o->cant=cp;
			o->nombreP =p->nombre;
			
			if(p->precio >= 500000 && p->precio<=1000000){
				seguro=cp*30000;
			}if(p->precio >= 1000001 && p->precio<=5000000){
				seguro=cp*120000;
			}else if(p->precio > 5000000){
				seguro=cp*170000;
			}
			if(c->tp =='E' && p->precio<2000000 && cp<5){
				float x;
				x= p->precio - ((p->precio)*0.19);
				p->precio =x;
			}
			if(cp>=6 && cp<=10){
				float x;
				x=p->precio - ((p->precio)*0.05);
				p->precio=x;
			}else if(cp>=11 && cp<=15){
				float x;
				x=p->precio - ((p->precio)*0.1);
				p->precio=x;
			}else if(cp>15){
				float x;
				x=p->precio - ((p->precio)*0.15);
				p->precio=x;
			}
			total=(p->precio*cp)+seguro;
			o->total =total;
			
			ordenBin.write((char *) &o, sizeof(Orden));
			
			salida<<setw(5)<<p->codigo<<"	"<<setw(20)<<p->nombre<<"  "<<setw(18)<<p->precio<<"    "<<setw(20)<<cp<<"       "<<setw(20)<<total<<endl;
			bool j;
			cout<<"Desea ordenar otro producto? (1=si)(0=no)"<<endl;
			cin>>j;
			if(j){
				w--;
			}else if(!j){
				w=0;	
			}
			producto.close();
		}else if(!b){
			cout<<"No hay ningun producto con ese codigo"<<endl;
			cout<<w;
		}
	}while(w!=0);
	
	cliente.close();
	salida.close();
	ordenBin.close();
}

void reporteVentas(){
	ifstream venta;
	venta.open("reporte.txt", ios::in);
	
	while(!venta.eof()){
		string linea;
		getline(venta, linea, '\n');
		cout<<linea<<endl;
	}
	venta.close();
}

void ordenes(){
	ifstream orden;
	orden.open("ordenes.dat", ios::in|ios::binary);
	Orden ord;
	Orden *o;
	o=&ord;
	cout<<"N-Orden	  N-Documento      Nombre	  Producto	   Cantidad	      Total"<<endl;
	while(!orden.eof()){
		orden.read((char *) &o, sizeof(Orden));
		cout<<o->n<<" "<<o->identificacion<<" "<<o->nombre<<" "<<o->nombreP<<" "<<o->cant<<" "<<o->total<<endl;
	}
	
	orden.close();
}

void modificarCompra(){
	fstream orden;
	orden.open("ordenes.dat", ios::in|ios::out|ios::binary);
	Orden ordenes[5];
	Orden *o;
	int ord, i=0;
	cout<<"Digite el numero de orden a modificar"<<endl;
	cin>>ord;
	
	while(!orden.eof()){
		orden.read((char *) &o, sizeof(Orden));
		if(o->n==ord){
			ordenes[i] = *o;
			i++;
		}
	}
	bool b=1;
	do{
		cout<<"# Orden: "<<ord<<endl;
		cout<<"# Identificacion: "<<ordenes[0].identificacion<<"		Nombre: "<<ordenes[0].nombre<<endl;
		for(int j=0; j<i;j++){
			cout<<j+1<<") Producto: "<<ordenes[j].nombreP<<"	  Cantidad: "<<ordenes[j].cant<<"     Total: "<<ordenes[j].total<<endl;
		}
		int aux;
		string nom;
		cout<<"Elige un producto de la orden a modificar"<<endl;
		cin>>aux;
		modificar(ordenes, aux);
		cout<<"Deseas modificar otro producto? (1=si)(0=no)"<<endl;	
		cin>>b;
	}while(b!=0);
	orden.close();
	
	orden.open("ordenes.dat", ios::in|ios::app|ios::binary);
	int q=0;
	while(!orden.eof()){
		Orden o1;
		orden.read((char *)&o1, sizeof(Orden));
		if(o1.n==ord){
			o1=ordenes[q];
			orden.write((char *) &o1, sizeof(Orden));
			i++;
		}
	}
	
	orden.close();	
}

void modificar(Orden ordenes[], int aux){
	int x, precio;
	float total;
	if(aux==1){
		cout<<"Digite la nueva cantidad"<<endl;
		cin>>x;
		precio= ordenes[0].total/ordenes[0].cant;
		ordenes[0].cant=x;
		total= precio*x;
		ordenes[0].total =total;
	}else if(aux==2){
		cout<<"Digite la nueva cantidad"<<endl;
		cin>>x;
		precio= ordenes[1].total/ordenes[1].cant;
		ordenes[1].cant=x;
		total= precio*x;
		ordenes[1].total =total;
	}else if(aux==3){
		cout<<"Digite la nueva cantidad"<<endl;
		cin>>x;
		precio= ordenes[2].total/ordenes[2].cant;
		ordenes[2].cant=x;
		total= precio*x;
		ordenes[2].total =total;
	}else if(aux==4){
		cout<<"Digite la nueva cantidad"<<endl;
		cin>>x;
		precio= ordenes[3].total/ordenes[3].cant;
		ordenes[3].cant=x;
		total= precio*x;
		ordenes[3].total =total;
	}else if(aux==5){
		cout<<"Digite la nueva cantidad"<<endl;
		cin>>x;
		precio= ordenes[4].total/ordenes[4].cant;
		ordenes[4].cant=x;
		total= precio*x;
		ordenes[4].total =total;
	}else {
		cout<<"Digite una opcion valida"<<endl;
	}
	
}

Orden * cargarOrdenes(){
	ifstream archivoBin;
	archivoBin.open("ordenes.dat",ios::out|ios::binary);
	Orden * ordenes = 0, * ordenesCpy = 0;
	Orden aux;
	int numOrd=0;
	if(archivoBin.fail())
	{
		cout <<"El archivo no se pudo abrir";
		exit(1);
	}
	
	while(!archivoBin.eof()){
		archivoBin.read((char*)&aux,sizeof(Orden));
		if(ordenes == NULL){
			ordenes = new Orden[numOrd + 1];	
		}else{
			ordenesCpy = ordenes;
			ordenes = new Orden[numOrd + 1];	 
			for(int i=0;i<numOrd;i++)
			{
				*(ordenes+i) = *(ordenesCpy+i);
			}
			delete [] ordenesCpy;
		}
		*(ordenes+numOrd) = aux;
		numOrd++;
	}
	archivoBin.close();
	return ordenes;
}

Producto * cargarProducto(){
	ifstream archivo;
	Producto * productos = 0;
	Producto * productosCpy = 0;
	int numProductos=0;
	archivo.open("productos.txt", ios::in);
	if(archivo.fail())
	{
		cout <<"El archivo no se pudo abrir"<<endl;
		exit(1);
	}
	
	while(!archivo.eof()){
			
		if(productos == NULL){
			productos = new Producto[numProductos+1];
		}else{
			productosCpy = productos;
			productos = new Producto[numProductos+1];
			for(int i=0;i<numProductos;i++){
				*(productos+i)=*(productosCpy+i);	
			}
			if(productosCpy != NULL){
				delete [] productosCpy;
			}	
		}
		archivo>>(productos+numProductos)->codigo;
		archivo.ignore(2, ',');
		getline(archivo, (productos+numProductos)->nombre, ',');
		archivo>>(productos+numProductos)->precio;
		archivo.ignore(2, ',');
		archivo>>(productos+numProductos)->cant;
				
		numProductos++;
	}
	archivo.close();
	return productos;
}

Cliente * cargarCliente(){
	ifstream archivo;
	Cliente * clientes = 0;
	Cliente * clientesCpy = 0;
	int numclientes=0;
	archivo.open("clientes.txt", ios::in);
	if(archivo.fail())
	{
		cout <<"El archivo no se pudo abrir"<<endl;
		exit(1);
	}
	
	while(!archivo.eof()){
		if(clientes == NULL)
		{
			clientes = new Cliente[numclientes+1];
		}else{
			clientesCpy = clientes;
			clientes = new Cliente[numclientes+1];
			for(int i=0;i<numclientes;i++){
				*(clientes+i)=*(clientesCpy+i);	
			}
			if(clientesCpy != NULL)
			delete [] clientesCpy;

		}
		archivo>>(clientes+numclientes)->tp;
		archivo.ignore(2, ',');
		archivo>>(clientes+numclientes)->documento;
		archivo.ignore(2, ',');
		getline(archivo, (clientes+numclientes)->nombre, ',');
		archivo>>(clientes+numclientes)->direccion;
		
		numclientes++;
	}
	archivo.close();
	return clientes;
}

