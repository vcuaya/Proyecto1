#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>

using namespace std;

void Cabecera()
{
    system("cls");
    cout << "Planificador de procesos";
    cout << "\nCreado por V�ctor Cuaya y Jared Torres\n";
}

void Menu()
{
    Cabecera();
    cout << "\n1) Crear procesos desde arhivo \"Procesos.txt\".";
    cout << "\n2) Capturar o agregar procesos.";
    cout << "\n3) Mostrar procesos.";
    cout << "\n4) Eliminar procesos.";
    cout << "\n5) Ejecutar planificador.";
    cout << "\n0) Salir.\n";
}

void SubMenu()
{
    Cabecera();
    cout << "\n1) .";
    cout << "\n2) .";
    cout << "\n3) .";
    cout << "\n4) .";
    cout << "\n5) .";
    cout << "\n0) Regresar.\n";
}

template <typename Tipo>
Tipo Lectura(string mensaje)
{
    Tipo valor;
    cout << endl << mensaje << endl;
    cin >> valor;
    return valor;
}


class Proceso
{
    unsigned short int idProceso;
    unsigned short int tLlegada;
    unsigned short int tEjecucion;
    unsigned short int prioridad;
    unsigned short int tFinalizacion;
public:
    Proceso() {};
    Proceso(unsigned short int idProceso, unsigned short int tLlegada, unsigned short int tEjecucion, unsigned short int prioridad)
    {
        this->idProceso = idProceso;
        this->tLlegada = tLlegada;
        this->tEjecucion = tEjecucion;
        this->prioridad = prioridad;
        tFinalizacion = 0;
    }
    void setID(unsigned short int idProceso)
    {
        this->idProceso = idProceso;
    }
    int getT_Id()
    {
        return idProceso;
    }
    int getT_Llegada()
    {
        return tLlegada;
    }
    void setT_Ejecucion(int tEjecucion)
    {
        this->tEjecucion = tEjecucion;
    }
    int getT_Ejecucion()
    {
        return tEjecucion;
    }
    void setT_Finalizacion(int tFinalizacion)
    {
        this->tFinalizacion = tFinalizacion;
    }
    int getT_Finalizacion()
    {
        return tFinalizacion;
    }
    int getT_prioridad()
    {
        return prioridad;
    }
    bool operator <(const Proceso &proceso) const
    {
        return idProceso < proceso.idProceso;
    }
    bool operator ==(const Proceso &proceso) const
    {
        return idProceso == proceso.idProceso;
    }
    friend ostream& operator<<(ostream& os, const Proceso &proceso);
    friend class CompararID;
    friend class CompararEjecucion;
    friend class CompararPrioridad;
    friend class CompararFinalizacion;
    friend class EliminarElemento;

    friend void MonoTareaMonoProceso(list<Proceso> &procesos, char plan[]);
    friend void MonoTareaMultiProceso(list<Proceso> &procesos, char plan[]);
    friend void MultiTareaMonoProceso(list<Proceso> &procesos, char plan[]);
    friend void MultiTareaMultiProceso(list<Proceso> &procesos, char plan[]);
};

class CompararID
{
public:
    bool operator ()(const Proceso& proceso1, const Proceso & proceso2)
    {
        if(proceso1.idProceso == proceso2.idProceso)
            return proceso1 < proceso2;
        return proceso1.idProceso < proceso2.idProceso;
    }
};

class CompararEjecucion
{
public:
    bool operator ()(const Proceso& proceso1, const Proceso& proceso2)
    {
        if(proceso1.tEjecucion == proceso2.tEjecucion)
            return proceso1 < proceso2;
        return proceso1.tEjecucion < proceso2.tEjecucion;
    }
};

class CompararPrioridad
{
public:
    bool operator ()(const Proceso& proceso1, const Proceso & proceso2)
    {
        if(proceso1.prioridad == proceso2.prioridad)
            return proceso1 < proceso2;
        return proceso1.prioridad < proceso2.prioridad;
    }
};

class CompararFinalizacion
{
public:
    bool operator ()(const Proceso& proceso1, const Proceso & proceso2)
    {
        if(proceso1.tFinalizacion == proceso2.tFinalizacion)
            return proceso1 < proceso2;
        return proceso1.tFinalizacion < proceso2.tFinalizacion;
    }
};

class EliminarElemento
{
public:
    bool operator ()(const Proceso& proceso1, const Proceso& proceso2)
    {
        return proceso1 == proceso2;
    }
};

ostream & operator <<(ostream& os, const Proceso& proceso)
{
    os << "     PID: "                << proceso.idProceso
       << "     T. Llegada: "         << proceso.tLlegada
       << "     T. Ejecuci�n: "       << proceso.tEjecucion
       << "     Prioridad: "          << proceso.prioridad
       << "     T. Finalizaci�n: "    << proceso.tFinalizacion
       << endl;
    return os;
}

void LecturaArchivo(list<Proceso> &procesos)
{
    unsigned short int idProceso = 0;
    unsigned short int tLlegada = 0;
    unsigned short int tEjecucion = 0;
    unsigned short int prioridad = 0;

    ifstream archivoLectura("Procesos.txt");
    if(!archivoLectura)
        cout << "\nEl archivo no se pudo abrir\n";
    else
    {
        while(archivoLectura>>idProceso>>tLlegada>>tEjecucion>>prioridad)
            procesos.push_back(Proceso(idProceso, tLlegada, tEjecucion, prioridad));
        archivoLectura.close();
        Cabecera();
        cout << "\nSe carg� el archivo correctamente\n";
    }
}

void MostrarLista(list<Proceso> &procesos)
{
    float total = 0;
    float promedio = 0;
    float unidades = 0;

    cout << "\nLos procesos registrados son:\n" << endl;
    procesos.sort(CompararID());
    for(Proceso& proceso: procesos)
    {
        cout << proceso;
        unidades += (proceso.getT_Finalizacion() - proceso.getT_Llegada() - proceso.getT_Ejecucion());
        total++;
    }
    cout << endl;
    promedio = unidades / total;
    if(promedio >= 0)
    {
        cout << "\nTiempo de espera total: " << (int)unidades << " unidades de ejecuci�n\n";
        cout << "\nTiempo de espera promedio: " << fixed << setprecision(2) << promedio << " unidades de ejecuci�n\n" << endl;
    }
}


/////////////////////////////////////////////////////

void Ordenamiento(list<Proceso> &procesos,list<Proceso>sac,list<Proceso> ordenada, char plan[])
{
    int i = 0;

    Proceso procesoaux;
    Proceso procesoaux2;

    list<Proceso> sacados;
    list<Proceso> aux;
    list<Proceso> procesoscopia;

    procesoscopia = procesos;

    while(i != 3)
    {
        switch(plan[i])
        {
        case 'A':
            procesoscopia.sort(CompararPrioridad());
            procesoaux = procesoscopia.front();
            while(!procesoscopia.empty())
            {
                procesoaux2 = procesoscopia.front();
                if(procesoaux.getT_prioridad() == procesoaux2.getT_prioridad())
                {
                    aux.push_back(procesoscopia.front());
                    procesoscopia.pop_front();
                }
                else
                {
                    sacados.push_back(procesoscopia.front());
                    procesoscopia.pop_front();
                }
            }
            while(!aux.empty())
            {
                procesoscopia.push_back(aux.front());
                aux.pop_front();
            }
            i++;
            break;
        case 'B':
            procesoscopia.sort(CompararPrioridad());
            procesoscopia.reverse();
            procesoaux = procesoscopia.front();
            while(!procesoscopia.empty())
            {
                procesoaux2 = procesoscopia.front();
                if(procesoaux.getT_prioridad() == procesoaux2.getT_prioridad())
                {
                    aux.push_back(procesoscopia.front());
                    procesoscopia.pop_front();
                }
                else
                {
                    sacados.push_back(procesoscopia.front());
                    procesoscopia.pop_front();
                }
            }
            while(!aux.empty())
            {
                procesoscopia.push_back(aux.front());
                aux.pop_front();
            }
            i++;
            break;
        case 'L':
            procesoscopia.sort(CompararEjecucion());
            procesoaux = procesoscopia.front();
            while(!procesoscopia.empty())
            {
                procesoaux2 = procesoscopia.front();
                if(procesoaux.getT_Ejecucion() == procesoaux2.getT_Ejecucion())
                {
                    aux.push_back(procesoscopia.front());
                    procesoscopia.pop_front();
                }
                else
                {
                    sacados.push_back(procesoscopia.front());
                    procesoscopia.pop_front();
                }
            }
            while(!aux.empty())
            {
                procesoscopia.push_back(aux.front());
                aux.pop_front();
            }
            i++;
            break;
        case 'P':
            procesoscopia.sort(CompararEjecucion());
            procesoscopia.reverse();
            procesoaux = procesoscopia.front();
            while(!procesoscopia.empty())
            {
                procesoaux2 = procesoscopia.front();
                if(procesoaux.getT_Ejecucion() == procesoaux2.getT_Ejecucion())
                {
                    aux.push_back(procesoscopia.front());
                    procesoscopia.pop_front();
                }
                else
                {
                    sacados.push_back(procesoscopia.front());
                    procesoscopia.pop_front();
                }
            }
            while(!aux.empty())
            {
                procesoscopia.push_back(aux.front());
                aux.pop_front();
            }
            i++;
            //milista.reverse();
            break;
        case 'U':
            procesoscopia.sort(CompararID());
            procesoaux = procesoscopia.front();
            while(!procesoscopia.empty())
            {
                procesoaux2 = procesoscopia.front();
                if(procesoaux.getT_Id() == procesoaux2.getT_Id())
                {
                    aux.push_back(procesoscopia.front());
                    procesoscopia.pop_front();
                }
                else
                {
                    sacados.push_back(procesoscopia.front());
                    procesoscopia.pop_front();
                }
            }
            while(!aux.empty())
            {
                procesoscopia.push_back(aux.front());
                aux.pop_front();
            }
            i++;
            break;
        case 'D':
            procesoscopia.sort(CompararID());
            procesoscopia.reverse();
            procesoaux = procesoscopia.front();
            while(!procesoscopia.empty())
            {
                procesoaux2 = procesoscopia.front();
                if(procesoaux.getT_Id() == procesoaux2.getT_Id())
                {
                    aux.push_back(procesoscopia.front());
                    procesoscopia.pop_front();
                }
                else
                {
                    sacados.push_back(procesoscopia.front());
                    procesoscopia.pop_front();
                }
            }
            while(!aux.empty())
            {
                procesoscopia.push_back(aux.front());
                aux.pop_front();
            }
            i++;
            break;
        default:
            cout << "El ordenamiento ingresado no es valido" << endl;
        }
    }
    if(!sacados.empty())
    {
        sac = sacados;
        procesos.remove(procesoscopia.front());
        ordenada.push_back(procesoscopia.front());
        /*cout<<"stock"<<endl;
        for(Proceso& proceso: procesos)
            cout << proceso;
        cout << endl;
        cout<<"ordenada"<<endl;
        for(Proceso& proceso: ordenada)
            cout << proceso;
        cout << endl;
        cout<<"sacados"<<endl;
        for(Proceso& proceso: sacados)
            cout << proceso;
        cout << endl;

        system("pause");*/
        Ordenamiento(procesos, sac, ordenada, plan);
    }
    else
    {
        if(!procesoscopia.empty())
        {
            ordenada.push_back(procesoscopia.front());
        }
        if(!ordenada.empty())
        {
            procesos=ordenada;
        }
    }
}
//////////////////////////////////////

void MonoTareaMonoProceso(list<Proceso> &procesos, char plan[])
{
    int ciclo = 0;

    bool core1 = true;

    Proceso enEjecucion1;

    list<Proceso> enEspera;
    list<Proceso> auxiliar;

    //PARAMETROS PARA EL ORDENAMIENTO
    list<Proceso> sac;
    list<Proceso> ord;
    ////////////////////////////////

    auxiliar = procesos;


    do
    {
        for(Proceso& proceso: auxiliar)
            if(proceso.getT_Llegada() == ciclo)
                enEspera.push_back(proceso);

        //Ordenamos como lo pide el usuario No implementado
        //enEspera.sort();
        //cout << "Ciclo " << ciclo << endl;
        //MostrarLista(enEspera);
        Ordenamiento(enEspera, sac, ord, plan);
        //cout << "Lista Ordenada " << ciclo << endl;
        //MostrarLista(enEspera);

        //////////////////////

        if(!core1)
        {
            if(enEjecucion1.getT_Ejecucion() == 0)
            {
                core1 = true;
                for(Proceso& proceso: procesos)
                    if(proceso == enEjecucion1)
                        proceso.setT_Finalizacion(ciclo);
                auxiliar.remove(enEjecucion1);
                //cout << "Proceso Libre\n" << enEjecucion1 << endl;
            }
            else
                enEjecucion1.setT_Ejecucion(enEjecucion1.getT_Ejecucion()-1);
        }

        if(!enEspera.empty() && core1)//Libre
        {
            core1 = false;
            enEjecucion1 = enEspera.front();
            enEspera.remove(enEjecucion1);
            enEjecucion1.setT_Ejecucion(enEjecucion1.getT_Ejecucion()-1);
            //cout << "Proceso en Ejecuci�n\n" << enEjecucion1 << endl;
        }
        //system("pause");
        //system("cls");
        ciclo++;
    }
    while(!core1 && !auxiliar.empty());
}

void MonoTareaMultiProceso(list<Proceso> &procesos, char plan[])
{
    int ciclo = 0;

    bool core1 = true;
    bool core2 = true;
    bool core3 = true;
    bool core4 = true;

    Proceso enEjecucion1;
    Proceso enEjecucion2;
    Proceso enEjecucion3;
    Proceso enEjecucion4;

    list<Proceso> enEspera;
    list<Proceso> auxiliar;

    //PARAMETROS PARA EL ORDENAMIENTO
    list<Proceso> sac;
    list<Proceso> ord;
    ////////////////////////////////


    auxiliar = procesos;

    do
    {
        for(Proceso& proceso: auxiliar)
            if(proceso.getT_Llegada() == ciclo)
                enEspera.push_back(proceso);

        //Ordenamos como lo pide el usuario
        //enEspera.sort();
        //cout << "Ciclo " << ciclo << endl;
        //MostrarLista(enEspera);
        Ordenamiento(enEspera, sac, ord, plan);
        //cout << "Lista Ordenada " << ciclo << endl;
        //MostrarLista(enEspera);
        //////////////////////////


        if(!core1)
        {
            if(enEjecucion1.getT_Ejecucion() == 0)
            {
                core1 = true;
                for(Proceso& proceso: procesos)
                    if(proceso == enEjecucion1)
                        proceso.setT_Finalizacion(ciclo);
                auxiliar.remove(enEjecucion1);
                //cout << "Proceso Libre\n" << enEjecucion1 << endl;
            }
            else
                enEjecucion1.setT_Ejecucion(enEjecucion1.getT_Ejecucion()-1);
        }
        if(!core2)
        {
            if(enEjecucion2.getT_Ejecucion() == 0)
            {
                core2 = true;
                for(Proceso& proceso: procesos)
                    if(proceso == enEjecucion2)
                        proceso.setT_Finalizacion(ciclo);
                auxiliar.remove(enEjecucion2);
                //cout << "Proceso Libre\n" << enEjecucion2 << endl;
            }
            else
                enEjecucion2.setT_Ejecucion(enEjecucion2.getT_Ejecucion()-1);
        }
        if(!core3)
        {
            if(enEjecucion3.getT_Ejecucion() == 0)
            {
                core3 = true;
                for(Proceso& proceso: procesos)
                    if(proceso == enEjecucion3)
                        proceso.setT_Finalizacion(ciclo);
                auxiliar.remove(enEjecucion3);
                //cout << "Proceso Libre\n" << enEjecucion3 << endl;
            }
            else
                enEjecucion3.setT_Ejecucion(enEjecucion3.getT_Ejecucion()-1);
        }
        if(!core4)
        {
            if(enEjecucion4.getT_Ejecucion() == 0)
            {
                core4 = true;
                for(Proceso& proceso: procesos)
                    if(proceso == enEjecucion4)
                        proceso.setT_Finalizacion(ciclo);
                auxiliar.remove(enEjecucion4);
                //cout << "Proceso Libre\n" << enEjecucion4 << endl;
            }
            else
                enEjecucion4.setT_Ejecucion(enEjecucion4.getT_Ejecucion()-1);
        }
        if(!enEspera.empty() && core1)//Libre
        {
            core1 = false;
            enEjecucion1 = enEspera.front();
            enEspera.remove(enEjecucion1);
            enEjecucion1.setT_Ejecucion(enEjecucion1.getT_Ejecucion()-1);
            //cout << "Proceso en Ejecuci�n\n" << enEjecucion1 << endl;
        }
        if(!enEspera.empty() && core2)//Libre
        {
            core2 = false;
            enEjecucion2 = enEspera.front();
            enEspera.remove(enEjecucion2);
            enEjecucion2.setT_Ejecucion(enEjecucion2.getT_Ejecucion()-1);
            //cout << "Proceso en Ejecuci�n\n" << enEjecucion2 << endl;
        }
        if(!enEspera.empty() && core3)//Libre
        {
            core3 = false;
            enEjecucion3 = enEspera.front();
            enEspera.remove(enEjecucion3);
            enEjecucion3.setT_Ejecucion(enEjecucion3.getT_Ejecucion()-1);
            //cout << "Proceso en Ejecuci�n\n" << enEjecucion3 << endl;
        }
        if(!enEspera.empty() && core4)//Libre
        {
            core4 = false;
            enEjecucion4 = enEspera.front();
            enEspera.remove(enEjecucion4);
            enEjecucion4.setT_Ejecucion(enEjecucion4.getT_Ejecucion()-1);
            //cout << "Proceso en Ejecuci�n\n" << enEjecucion4 << endl;
        }
        //system("pause");
        //system("cls");
        ciclo++;
    }
    while((!core1 || !core2 || !core3 || !core4) && !auxiliar.empty());
}

void MultiTareaMonoProceso(list<Proceso> &procesos, char plan[])
{
    int ciclo = 0;

    Proceso enEjecucion1;

    list<Proceso> enEspera;
    list<Proceso> porEjecutar;

    //PARAMETROS PARA EL ORDENAMIENTO
    list<Proceso> sac;
    list<Proceso> ord;
    ////////////////////////////////

    do
    {
        if(!porEjecutar.empty())
        {
            if(!enEspera.empty())
            {
                for(Proceso& procesoEspera: enEspera)
                {
                    if(procesoEspera.getT_Ejecucion() == 0)
                    {
                        for(Proceso& procesoTerminado: procesos)
                            if(procesoTerminado == procesoEspera)
                                procesoTerminado.setT_Finalizacion(ciclo);
                        enEspera.remove(procesoEspera);
                    }
                }
            }
        }
        else
        {
            if(!enEspera.empty())
            {
                for(Proceso& procesoEspera: enEspera)
                {
                    if(procesoEspera.getT_Ejecucion() == 0)
                    {
                        for(Proceso& procesoTerminado: procesos)
                            if(procesoTerminado == procesoEspera)
                                procesoTerminado.setT_Finalizacion(ciclo);
                        enEspera.remove(procesoEspera);
                        //cout << "Proceso Libre\n" << enEjecucion1 << endl;
                    }
                    else
                        porEjecutar.push_back(procesoEspera);
                }
            }
            enEspera.clear();
        }
        for(Proceso& proceso: procesos)
            if(proceso.getT_Llegada() == ciclo)
                porEjecutar.push_back(proceso);

        //Ordenamos porEjecutar
        //porEjecutar.sort();
        //cout << "Ciclo " << ciclo << endl;
        //MostrarLista(porEjecutar);
        Ordenamiento(porEjecutar, sac, ord, plan);
        //cout << "Lista Ordenada " << ciclo << endl;
        //MostrarLista(porEjecutar);
        ////////////////

        if(!porEjecutar.empty())//Nucleo 1
        {
            enEjecucion1 = porEjecutar.front();
            porEjecutar.remove(enEjecucion1);
            enEspera.remove(enEjecucion1);
            enEjecucion1.setT_Ejecucion(enEjecucion1.getT_Ejecucion()-1);
            enEspera.push_back(enEjecucion1);
            //cout << "Proceso en Ejecuci�n\n" << enEjecucion1 << endl;
        }
        //system("pause");
        //system("cls");
        ciclo++;
    }
    while(!enEspera.empty());
}

void MultiTareaMultiProceso(list<Proceso> &procesos, char plan[])
{
    int ciclo = 0;

    Proceso enEjecucion1;
    Proceso enEjecucion2;
    Proceso enEjecucion3;
    Proceso enEjecucion4;

    list<Proceso> enEspera;
    list<Proceso> porEjecutar;

    //PARAMETROS PARA EL ORDENAMIENTO
    list<Proceso> sac;
    list<Proceso> ord;
    ////////////////////////////////

    do
    {
        if(!porEjecutar.empty())
        {
            if(!enEspera.empty())
            {
                for(Proceso& procesoEspera: enEspera)
                {
                    if(procesoEspera.getT_Ejecucion() == 0)
                    {
                        for(Proceso& procesoTerminado: procesos)
                            if(procesoTerminado == procesoEspera)
                                procesoTerminado.setT_Finalizacion(ciclo);
                        enEspera.remove(procesoEspera);
                    }
                }
            }
        }
        else
        {
            if(!enEspera.empty())
            {
                for(Proceso& procesoEspera: enEspera)
                {
                    if(procesoEspera.getT_Ejecucion() == 0)
                    {
                        for(Proceso& procesoTerminado: procesos)
                            if(procesoTerminado == procesoEspera)
                                procesoTerminado.setT_Finalizacion(ciclo);
                        enEspera.remove(procesoEspera);
                        //cout << "Proceso Libre\n" << procesoEspera << endl;
                    }
                    else
                        porEjecutar.push_back(procesoEspera);
                }
            }
            enEspera.clear();
        }
        for(Proceso& proceso: procesos)
            if(proceso.getT_Llegada() == ciclo)
                porEjecutar.push_back(proceso);

        //Ordenamos porEjecutar
        //porEjecutar.sort();
        //cout << "Ciclo " << ciclo << endl;
        //MostrarLista(porEjecutar);
        Ordenamiento(porEjecutar, sac, ord, plan);
        //cout << "Lista Ordenada " << ciclo << endl;
        //MostrarLista(porEjecutar);
        ///////////////////

        if(!porEjecutar.empty())//Nucleo 1
        {
            enEjecucion1 = porEjecutar.front();
            porEjecutar.remove(enEjecucion1);
            enEspera.remove(enEjecucion1);
            enEjecucion1.setT_Ejecucion(enEjecucion1.getT_Ejecucion()-1);
            enEspera.push_back(enEjecucion1);
            //cout << "Proceso en Ejecuci�n\n" << enEjecucion1 << endl;
        }
        if(!porEjecutar.empty())//Nucleo 2
        {
            enEjecucion2 = porEjecutar.front();
            porEjecutar.remove(enEjecucion2);
            enEspera.remove(enEjecucion2);
            enEjecucion2.setT_Ejecucion(enEjecucion2.getT_Ejecucion()-1);
            enEspera.push_back(enEjecucion2);
            //cout << "Proceso en Ejecuci�n\n" << enEjecucion2 << endl;
        }
        if(!porEjecutar.empty())//Nucleo 3
        {
            enEjecucion3 = porEjecutar.front();
            porEjecutar.remove(enEjecucion3);
            enEspera.remove(enEjecucion3);
            enEjecucion3.setT_Ejecucion(enEjecucion3.getT_Ejecucion()-1);
            enEspera.push_back(enEjecucion3);
            //cout << "Proceso en Ejecuci�n\n" << enEjecucion3 << endl;
        }
        if(!porEjecutar.empty())//Nucleo 4
        {
            enEjecucion4 = porEjecutar.front();
            porEjecutar.remove(enEjecucion4);
            enEspera.remove(enEjecucion4);
            enEjecucion4.setT_Ejecucion(enEjecucion4.getT_Ejecucion()-1);
            enEspera.push_back(enEjecucion4);
            //cout << "Proceso en Ejecuci�n\n" << enEjecucion4 << endl;
        }
        //system("pause");
        //system("cls");
        ciclo++;
    }
    while(!enEspera.empty());
}

int main()
{
    //Configura los caracteres en Espa�ol
    setlocale(LC_CTYPE, "spanish");

    /////////////VARIABLES DE ORDENAMIENTO
    list<Proceso> sac;
    list<Proceso> ord;
    char plan[3];
    /////////////////////////////////

    //Declaraci�n de Variables
    int num = 0;
    int tTotal = 0;

    char opc=NULL;

    bool idExiste = false;

    unsigned short int idProceso = 0;
    unsigned short int tLlegada = 0;
    unsigned short int tEjecucion = 0;
    unsigned short int prioridad = 0;

    list <Proceso> procesos;

    Proceso auxiliar;

    //Men� del programa
    do
    {
        Cabecera();
        Menu();
        opc = Lectura<char>("Introduce la opci�n deseada");
        switch(opc)
        {
        case '1':
            Cabecera();
            if(procesos.empty())
            {
                LecturaArchivo(procesos);
                cout << endl;
            }
            else
            {
                cout << "\nLa lista de procesos no est� vac�a, si previamente hab�as cargado los procesos podr�as duplicarlos.\n";
                cout << "�Deseas cargar elementos desde el archivo \"Procesos.txt\".?";
                cout << "\nSi/No (s/n).\n";
                opc = Lectura<char>("Introduce la opci�n deseada");
                if(opc == 's' | opc == 'S')
                {
                    LecturaArchivo(procesos);
                    cout << endl;
                }
                else
                    cout << "\nNo se cargaron los datos.\n";
            }

            system("pause");
            break;
        case '2':
            Cabecera();
            idProceso = Lectura<unsigned short int>("Introduce el ID del proceso");
            tLlegada = Lectura<unsigned short int>("Introduce el Tiempo de Llegada del proceso");
            tEjecucion = Lectura<unsigned short int>("Introduce el Tiempo de Ejecuci�n del proceso");
            prioridad = Lectura<unsigned short int>("Introduce la Prioridad del proceso");
            procesos.push_back(Proceso(idProceso, tLlegada, tEjecucion, prioridad));

            Cabecera();
            cout << "\nSe registr� el proceso:\n" << endl << procesos.back() << endl;

            system("pause");
            break;
        case '3':
            Cabecera();
            MostrarLista(procesos);

            system("pause");
            break;
        case '4':
            Cabecera();
            MostrarLista(procesos);

            idProceso = Lectura<unsigned short int>("Introduce el ID del proceso que deseas eliminar");
            auxiliar.setID(idProceso);

            for(Proceso& proceso: procesos)
                if(proceso == auxiliar)
                    idExiste = true;
            if(idExiste)
            {
                procesos.remove(auxiliar);
                cout << "\nSe elimin� el proceso con ID: " << idProceso << endl;
                MostrarLista(procesos);
            }
            else
                cout << "\nEl ID del proceso no existe\n";

            system("pause");
            break;
        case '5':
            {
            Cabecera();
            //SubMenu();

            ////////////////////
            cout <<"Personalice el planificador"<<endl;
                cout <<"1)Prioridad"<<endl;
                cout <<"2)Tiempo de ejecucion"<<endl;
                cout <<"3)Pid"<<endl;
                char opc2=NULL;
                opc2 = Lectura<char>("Introduce la opci�n deseada");
                switch(opc2)
                {
                    case'1':
                        {
                            cout <<"Eliga prioridad alta o baja (A/B)"<<endl;
                            cin>>plan[0];

                            system("cls");

                            cout <<"Seleccione el siguiente atributo"<<endl;
                            cout <<"1)Tiempo de ejecucion"<<endl;
                            cout << "2)Pid" <<endl;
                            char opc3 =NULL;
                            opc3 = Lectura<char>("Introduce la opci�n deseada");
                            switch(opc3)
                            {
                                case '1':
                                    cout <<"Eliga tiempo de ejecucion ligero o pesado (L/P)"<<endl;
                                    cin>>plan[1];

                                    system("cls");

                                    cout <<"Eliga pid ascendente o descendente (U/D)"<<endl;
                                    cin>>plan[2];

                                    break;
                                case '2':
                                    cout <<"Eliga pid ascendente o descendente (U/D)"<<endl;
                                    cin>>plan[1];

                                    system("cls");

                                    cout <<"Eliga tiempo de ejecucion ligero o pesado (L/P)"<<endl;
                                    cin>>plan[2];
                                    break;
                                default:
                                    cout << "Opcion invalida" <<endl;
                            }
                            break;
                        }
                    case '2':
                        {
                            cout <<"Eliga tiempo de ejecucion ligero o pesado (L/P)"<<endl;
                            cin>>plan[0];

                            system("cls");

                            cout <<"Seleccione el siguiente atributo"<<endl;
                            cout <<"1)Prioridad"<<endl;
                            cout << "2)Pid" <<endl;
                            char opc4 =NULL;
                            opc4 = Lectura<char>("Introduce la opci�n deseada");
                            switch(opc4)
                            {
                                case '1':
                                    cout <<"Eliga prioridad alta o baja (A/B)"<<endl;
                                    cin>>plan[1];

                                    system("cls");

                                    cout <<"Eliga pid ascendente o descendente (U/D)"<<endl;
                                    cin>>plan[2];

                                    break;
                                case '2':
                                    cout <<"Eliga pid ascendente o descendente (U/D)"<<endl;
                                    cin>>plan[1];

                                    system("cls");

                                    cout <<"Eliga prioridad alta o baja (A/B)"<<endl;
                                    cin>>plan[2];
                                    break;
                                default:
                                    cout << "Opcion invalida"<<endl;
                            }
                            break;
                        }

                    case '3':
                        {
                        cout <<"Eliga pid ascendente o descendente (U/D)"<<endl;
                        cin>>plan[0];

                        system("cls");

                        cout <<"Seleccione el siguiente atributo"<<endl;
                        cout <<"1)Prioridad"<<endl;
                        cout << "2)Tiempo de ejecucion" <<endl;
                        char opc5 =NULL;
                        opc5 = Lectura<char>("Introduce la opci�n deseada");
                        switch(opc5)
                        {
                            case '1':
                                cout <<"Eliga prioridad alta o baja (A/B)"<<endl;
                                cin>>plan[1];

                                system("cls");

                                cout <<"Eliga tiempo de ejecucion ligero o pesado (L/P)"<<endl;
                                cin>>plan[2];

                                break;
                            case '2':
                                cout <<"Eliga tiempo de ejecucion ligero o pesado (L/P)"<<endl;
                                cin>>plan[1];

                                system("cls");

                                cout <<"Eliga prioridad alta o baja (A/B)"<<endl;
                                cin>>plan[2];
                                break;
                            default:
                                cout << "Opcion invalida"<<endl;
                        }
                        break;
                        }
                    default:
                        cout << "opcion invalida" <<endl;
                }
            ///////////////////////////////////

            Cabecera();
            cout << "\nMonotarea Monoproceso:" << endl;
            MonoTareaMonoProceso(procesos, plan);
            MostrarLista(procesos);

            cout << "\nMonotarea Multiproceso:" << endl;
            MonoTareaMultiProceso(procesos, plan);
            MostrarLista(procesos);

            cout << "\nMultitarea Monoproceso:" << endl;
            MultiTareaMonoProceso(procesos, plan);
            MostrarLista(procesos);

            cout << "\nMultitarea Multiproceso:" << endl;
            MultiTareaMultiProceso(procesos, plan);
            MostrarLista(procesos);

            system("pause");
            break;
        }
        case '0':
            system("cls");
            cout<<"Programa finalizado\n";
            break;
        default:
            system("cls");
            cout<<"\aPor favor introduce una opci�n v�lida\n\n";
            system("pause");
            break;
        }
    }
    while(opc!='0');
    return 0;
}
