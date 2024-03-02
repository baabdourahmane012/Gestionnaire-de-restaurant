#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Gerer les clients
class Client {
    string prenom;
    string nom;
    int numeroTable;

    public:
    static int nombreClient;
    Client(const string &prenom, const string &nom, int table) : prenom(prenom), nom(nom)
    { nombreClient++; numeroTable = table; } 
    string getPrenom() const { return prenom; }
    string getNom() const { return nom; }
    int getNumeroTable() { return numeroTable; }
};
// Initialiser le nombre de client
int Client::nombreClient = 0;
// Gerer le menu et les tarifs
struct Menu {
    Client client;
    string recette;
};
// Menu disponibles
struct MenuDisponibles {
    string nom;
    double prix;
};
// Retrouver le prix d'un menu dans la liste des menus disponibles
double verifierPrix(const string &nom, vector<MenuDisponibles> menus) {
    for(auto menu : menus) {
        if (menu.nom == nom ) return menu.prix;
    }
}
// Gerer les commandes
class Commande{
    public:
    static vector<Menu> menus;
    int numeroTable;
    double prix;

    Commande(Menu m){
        menus.push_back(m);
    };
    // Supprimer un client
    static void supprimer(int table, vector<Client> &clients){
        auto it = find_if(clients.begin(), clients.end(), [&](Client& client) { return client.getNumeroTable() == table; }) ;
        if (it != clients.end()){ clients.erase(it); Client::nombreClient--; }
    }
    // Afficher les commandes
    static void afficher(int choixMenu, double addition, vector<Client> &clients) {
        int i = 0;
        cout << endl;
        for (auto client : clients) {
            cout << "\n\tClient: " << client.getPrenom() << " " << client.getNom();
            cout << "\n\tMenu: " << menus.at(choixMenu-1).recette;
            cout << "\n\tTable: " << client.getNumeroTable() << endl;
            cout << "\n\t[+] Addition: " << addition << "$" << endl;
            cout << "\t---------------------------------------" << endl << endl;
        }
    }
};
vector<Menu> Commande::menus = {};

int main(int argc, char const *argv[])
{
    int choix, table, choixMenu, tableVide, i=1;
    string nom, prenom, nomClient;
    vector<MenuDisponibles> menus = { {"Poulets", 5.99}, {"Burger Complet", 3.89}, {"Rataouille", 12.79}, {"Maffe Poulet", 6.86} };
    vector<Client> clients;
    cout << "\t[ 1 ] Enregistrer un client\n\t[ 2 ] Consulter Menus et Tarifs";
    cout << "\n\t[ 3 ] Prendre une commande\n\t[ 4 ] Gestion des commandes";
    cout << "\n\t[ 5 ] Gestion des clients\n\t[ 6 ] Quitter\n";
    while(choix != 6){
        cout << endl << "\t[OPTION] Choisir: ";
        cin>>choix;
        switch (choix)
        {
        case 1:
            cout << "\t\t - Enregistrer le client -\n\t\tNom: ";
            cin>>nom;
            cout << "\t\tPrenom: ";
            cin>>prenom;
            cout << "\t\tNumero table: ";
            cin>>table;
            clients.push_back(Client(nom, prenom, table));
            break;
        case 2:
            cout << "\t\t - Affichage des menus du jour -\n";
            for(auto menu : menus){
                cout << "\t["<<i<<"] "<< left << setw(20) << menu.nom << right << setw(20) << menu.prix << "$" << endl;
                i++;
            }
            i = 1;
            break;
        case 3:
            cout << "\t[ Menu du jour ]\n";
            for(auto menu : menus){
                cout << "\t["<<i<<"]"<< left << setw(15) << menu.nom << right << setw(15) << menu.prix << "$" << endl;
                i++;
            }
            i = 1;
            cout << "\t[#] Choisir [1~2]: ";
            cin>>choixMenu;
            cout << "\t[Client] Entrer: ";
            cin>>nomClient;
            for (auto client : clients){
                if(client.getNom() == nomClient){
                    Commande({client, menus.at(choixMenu-1).nom});
                    Commande::afficher(choixMenu, menus.at(choixMenu-1).prix, clients);
                    break;
                }
            }
            break;
        case 4:
            cout << "\t- Gestion des commandes -\n";
            cout << "\t[Supprimer client] Entrer la table: ";
            cin>>tableVide;
            for (auto client : clients){
                if(client.getNumeroTable() == tableVide){
                    Commande::supprimer(tableVide, clients);
                    break;
                }
            }
            break;
        case 5:
            cout << "\t[#] "<< "Prenom" << right << setw(18) << "Nom" << right << setw(10) << "Table" << endl;
            for(auto client : clients){
                cout << "\t["<<i<<"] "<< setw(20) << left << client.getPrenom() << client.getNom() << right << setw(10) 
                << client.getNumeroTable() << endl;
                i++;
            }
            cout << "\t[+] "<< left << "Total: " << Client::nombreClient << " clients"<< endl;
            i=1;
            break;
        default:
            break;
        }
    }
    return 0;
}
