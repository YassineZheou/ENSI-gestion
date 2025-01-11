#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Matiere {
    string nom;
    float moyenne;
};

struct Etudiant {
    string nom;
    vector<Matiere> matieres;
    float moyenneGenerale;
};

void afficherResultats(Etudiant &etudiant) {
    cout << "\n=== Resultats pour l'etudiant: " << etudiant.nom << " ===\n";
    bool doitRepasser = false;
    for (auto &matiere : etudiant.matieres) {
        if (matiere.moyenne < 8) {
            cout << "- " << matiere.nom << ": Repassage obligatoire (moyenne: " << matiere.moyenne << ")\n";
            doitRepasser = true;
        } else if (matiere.moyenne < 10) {
            cout << "- " << matiere.nom << ": Controle en juin (moyenne: " << matiere.moyenne << ")\n";
            doitRepasser = true;
        } else {
            cout << "- " << matiere.nom << ": Admis (moyenne: " << matiere.moyenne << ")\n";
        }
    }

    if (doitRepasser) {
        cout << "\nL'etudiant devra revenir au mois de juin pour repasser les matieres avec une moyenne inferieure a 10.\n";

        cout << "\n=== Matieres a repasser (moyenne < 8) ===\n";
        for (auto &matiere : etudiant.matieres) {
            if (matiere.moyenne < 8) {
                cout << "- " << matiere.nom << "\n";
            }
        }
    } else {
        cout << "\nL'etudiant est admis dans toutes les matieres.\n";
    }
}

void calculerMoyenneGenerale(Etudiant &etudiant) {
    float somme = 0;
    for (auto &matiere : etudiant.matieres) {
        somme += matiere.moyenne;
    }
    etudiant.moyenneGenerale = somme / etudiant.matieres.size();
    cout << "\n=== Moyenne generale: " << etudiant.moyenneGenerale << " ===\n";

    if (etudiant.moyenneGenerale >= 10) {
        cout << "L'etudiant est admis et passe a l'annee suivante.\n";
    } else {
        cout << "L'etudiant n'a pas atteint la moyenne generale de 10.\n";
        cout << "Il doit choisir 3 matieres parmi celles qu'il a echoue pour les repasser en juin.\n";
        cout << "Voici les matieres disponibles: \n";
        for (size_t i = 0; i < etudiant.matieres.size(); ++i) {
            if (etudiant.matieres[i].moyenne < 10) {
                cout << i + 1 << ". " << etudiant.matieres[i].nom << "\n";
            }
        }

        vector<string> matieresARepasser;
        for (int i = 0; i < 3; ++i) {
            int choix;
            cout << "Choisissez la matiere " << i + 1 << " a repasser: ";
            cin >> choix;
            while (choix < 1 || choix > etudiant.matieres.size() || etudiant.matieres[choix - 1].moyenne >= 10) {
                cout << "Choix invalide. Veuillez reessayer: ";
                cin >> choix;
            }
            matieresARepasser.push_back(etudiant.matieres[choix - 1].nom);
        }

        cout << "\nMatieres choisies pour repasser: \n";
        for (const auto &matiere : matieresARepasser) {
            cout << "- " << matiere << "\n";
        }
    }
}

int main() {
    Etudiant etudiant;
    cout << "Entrez le nom de l'etudiant: ";
    getline(cin, etudiant.nom);

    int nombreMatieres;
    cout << "Entrez le nombre de matieres: ";
    cin >> nombreMatieres;
    cin.ignore();

    for (int i = 0; i < nombreMatieres; ++i) {
        Matiere matiere;
        cout << "Entrez le nom de la matiere " << i + 1 << ": ";
        getline(cin, matiere.nom);
        cout << "Entrez la moyenne pour " << matiere.nom << ": ";
        cin >> matiere.moyenne;
        cin.ignore();
        etudiant.matieres.push_back(matiere);
    }

    afficherResultats(etudiant);
    calculerMoyenneGenerale(etudiant);

    return 0;
}
