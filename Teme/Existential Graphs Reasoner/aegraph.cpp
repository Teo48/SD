#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <utility>
#include <cassert>
#include "./aegraph.h"

std::string strip(std::string s) {
    // deletes whitespace from the beginning and end of the string
    s.erase(0, s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t")+1);
    return s;
}

std::pair<std::string, std::string> split_first(std::string s,
    char delimiter = ',') {
    // returns a pair that contains: <first_cut, rest_of_graph>

    int numOpen = 0;

    int len = s.size();
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == delimiter && numOpen == 0)
            return std::make_pair(
                    strip(s.substr(0, i)), strip(s.substr(i+1, len)));
        if (c == '[')
            numOpen += 1;
        if (c == ']')
            numOpen -= 1;
    }

    return {strip(s), std::string()};
}


std::vector<std::string> split_level(std::string s, char delimiter = ',') {
    // splits 's' into separate entities (atoms, subgraphs)

    std::vector<std::string> result;
    auto snd = s;
    while (true) {
        auto p = split_first(snd, delimiter);
        auto fst = p.first;
        snd = p.second;

        result.push_back(fst);

        if (snd.empty())
            return result;
    }
}


int AEGraph::num_subgraphs() const {
    return subgraphs.size();
}


int AEGraph::num_atoms() const {
    return atoms.size();
}


int AEGraph::size() const {
    return num_atoms() + num_subgraphs();
}


bool AEGraph::operator<(const AEGraph& other) const {
    return this->repr() < other.repr();
}

bool AEGraph::operator==(const AEGraph& other) const {
    return this->repr() == other.repr();
}

bool AEGraph::operator!=(const AEGraph& other) const {
    return this->repr() != other.repr();
}

AEGraph AEGraph::operator[](const int index) const {
    // offers an easier way of accessing the nested graphs
    if (index < num_subgraphs()) {
        return subgraphs[index];
    }

    if (index < num_subgraphs() + num_atoms()) {
        return AEGraph('(' + atoms[index - num_subgraphs()] + ')');
    }

    return AEGraph("()");
}

std::ostream& operator<<(std::ostream &out, const AEGraph &g) {
    out << g.repr();
    return out;
}

AEGraph::AEGraph(std::string representation) {
    // constructor that creates an AEGraph structure from a
    // serialized representation
    char left_sep = representation[0];
    char right_sep = representation[representation.size() - 1];

    assert((left_sep == '(' && right_sep == ')')
        || (left_sep == '[' && right_sep == ']'));

    // if the left separator is '(' then the AEGraph is the entire
    // sheet of assertion
    if (left_sep == '(') {
        is_SA = true;
    } else {
        is_SA = false;
    }

    // eliminate the first pair of [] or ()
    representation = representation.substr(1, representation.size() - 2);

    // split the graph into separate elements
    auto v = split_level(representation);
    // add them to the corresponding vector
    for (auto s : v) {
        if (s[0] != '[') {
            atoms.push_back(s);
        } else {
            subgraphs.push_back(AEGraph(s));
        }
    }

    // also internally sort the new graph
    this->sort();
}

std::string AEGraph::repr() const {
    // returns the serialized representation of the AEGraph

    std::string left, right;
    if (is_SA) {
        left = '(';
        right = ')';
    } else {
        left = '[';
        right = ']';
    }

    std::string result;
    for (auto subgraph : subgraphs) {
        result += subgraph.repr() + ", ";
    }

    int len = atoms.size();
    if (len != 0) {
        for (int i = 0; i < len - 1; i++) {
            result += atoms[i] + ", ";
        }
        result += atoms[len - 1];
    } else {
        if (subgraphs.size() != 0)
            return left + result.substr(0, result.size() - 2) + right;
    }

    return left + result + right;
}


void AEGraph::sort() {
    std::sort(atoms.begin(), atoms.end());

    for (auto& sg : subgraphs) {
        sg.sort();
    }

    std::sort(subgraphs.begin(), subgraphs.end());
}

bool AEGraph::contains(const std::string other) const {
    // checks if an atom is in a graph
    if (find(atoms.begin(), atoms.end(), other) != atoms.end())
        return true;

    for (const auto& sg : subgraphs)
        if (sg.contains(other))
            return true;

    return false;
}

bool AEGraph::contains(const AEGraph& other) const {
    // checks if a subgraph is in a graph
    if (find(subgraphs.begin(), subgraphs.end(), other) != subgraphs.end())
        return true;

    for (const auto& sg : subgraphs)
        if (sg.contains(other))
            return true;

    return false;
}

std::vector<std::vector<int>> AEGraph::get_paths_to(const std::string other)
    const {
    // returns all paths in the tree that lead to an atom like <other>
    std::vector<std::vector<int>> paths;

    int len_atoms = num_atoms();
    int len_subgraphs = num_subgraphs();

    for (int i = 0; i < len_atoms; i++) {
        if (atoms[i] == other && size() > 1) {
            paths.push_back({i + len_subgraphs});
        }
    }

    for (int i = 0; i < len_subgraphs; i++) {
        if (subgraphs[i].contains(other)) {
            auto r = subgraphs[i].get_paths_to(other);
            for (auto& v : r)
                v.insert(v.begin(), i);
            copy(r.begin(), r.end(), back_inserter(paths));
        }
    }

    return paths;
}

std::vector<std::vector<int>> AEGraph::get_paths_to(const AEGraph& other)
    const {
    // returns all paths in the tree that lead to a subgraph like <other>
    std::vector<std::vector<int>> paths;
    int len_subgraphs = num_subgraphs();

    for (int i = 0; i < len_subgraphs; i++) {
        if (subgraphs[i] == other && size() > 1) {
            paths.push_back({i});
        } else {
            auto r = subgraphs[i].get_paths_to(other);
            for (auto& v : r)
                v.insert(v.begin(), i);
            copy(r.begin(), r.end(), back_inserter(paths));
        }
    }

    return paths;
}

/*
    Functie ce ne intoarcea matricea cu pozitiile unde putem realiza operatia
    de double cut. Parcurgem fiecare subgraf, verificam daca indeplineste
    conditiile de double cut si retinem path-ul.
*/

std::vector<std::vector<int>> AEGraph::possible_double_cuts() const {
    std::vector<int>::iterator it;
    std::vector<int> temp;
    std::vector<std::vector<int>> temp_path, final_path;

    for (int i = 0 ; i < num_subgraphs(); ++i) {
    	temp.push_back(i);

    	if (subgraphs[i].size() && !subgraphs[i].num_atoms()) {
    		final_path.push_back(temp);
    	}

    	temp_path = subgraphs[i].possible_double_cuts();

    	for (unsigned int j = 0 ; j < temp_path.size() ; ++j) {
    		for(it = temp_path[j].begin() ; it != temp_path[j].end() ; ++it) {
    			temp.insert(temp.end(), *it);
    			final_path.push_back(temp);
    		}
    	}

    	temp.erase(temp.begin(), temp.end());
    }

	return final_path;
}

/*
    Functie ajutatoare pentru realizarea operatiei de double cut.
    Eliminam pe rand fiecare fiu din lista, intram in recursie pe
    subgrafurile fiecarui fiu pana cand lista noastra are un singur
    element. Eliminam taieturile care nu contin nimic intre ele si
    obtinem noul AEGraph.
*/

void utility_double_cut(AEGraph& aeg, std::vector<int> where) {
    if (where.size() == 1) {
        std::vector<std::string>::iterator it;
        for (it = aeg.subgraphs[where[0]].subgraphs[0].atoms.begin() ; it
                != aeg.subgraphs[where[0]].subgraphs[0].atoms.end() ; ++it) {
            aeg.atoms.push_back(*it);
        }

        aeg.subgraphs.erase(aeg.subgraphs.begin() + where[0]);
    } else if (aeg.contains(aeg.subgraphs[where[0]])) {
        int temp = where[0];
        where.erase(where.begin());
        utility_double_cut(aeg.subgraphs[temp], where);
    }
}

/*
    Functie ce realizeaza operatia de double_cut.
*/
AEGraph AEGraph::double_cut(std::vector<int> where) const {
    AEGraph nonConstThis = *this;
    utility_double_cut(nonConstThis, where);
	return nonConstThis;
}

/*
    Functie ce intoarce pozitiile unde putem realiza operatia de erase.
    Idem possible_double_cuts cu respectarea conditiilor impuse de erase
    si anume nu luam in calcul taietura care delimiteaza acel subgraf,
    sa nu stergem un graf daca este singur in taietura.
*/

std::vector<std::vector<int>> AEGraph::possible_erasures(int level) const {
    std::vector<std::vector<int>>::iterator it;
    std::vector<std::vector<int>> paths;
    for (int i = 0 ; i < size() ; ++i) {
        if (level % 2) {
            paths.push_back(std::vector<int>(1, i));
            if ((level != -1 && (!num_subgraphs() && num_atoms() == 1))
                || (level != -1 && (num_subgraphs() == 1 && !num_atoms()))) {
                paths.pop_back();
            }
        }

        if (num_subgraphs() > i) {
            std::vector<std::vector<int>> temp =
                subgraphs[i].possible_erasures(level + 1);

            for (std::vector<int> &aux : temp) {
                aux.insert(aux.begin(), i);
            }

            for (it = temp.begin() ; it != temp.end() ; ++it) {
                paths.insert(paths.begin(), *it);
            }
        }
    }

    return paths;
}

/*
    Functie ajutatoare pentru realizarea operatiei de erase.
    Stergem recursiv subgrafurile respectiv atomii din graful initial
    pe fiecare subgraf din lista(Daca primul nodul din lista este
    mai mare decat num_subgraph inseamna ca este frunza si trebuie sa
    stergem atomul de pe poztia where[0] - num_subraphs, altfel
    stergem subgraful de pe pozitia where[0]) si obtinem noul AEGraph.
*/

void utility_erase(AEGraph& aeg, std::vector<int> where) {
    if (where.size() == 1 && aeg.num_subgraphs() > where[0]) {
        aeg.subgraphs.erase(aeg.subgraphs.begin() + where[0]);
    } else if (where.size() == 1 && !(aeg.num_subgraphs() > where[0])) {
        aeg.atoms.erase(aeg.atoms.begin() + where[0] - aeg.num_subgraphs());
    } else if (aeg.contains(aeg.subgraphs[where[0]])) {
        int temp = where[0];
        where.erase(where.begin());
        utility_erase(aeg.subgraphs[temp], where);
    }
}

/*
    Functie ce realizeaza operatia de erase.
*/

AEGraph AEGraph::erase(std::vector<int> where) const {
    AEGraph nonConstThis = *this;
    utility_erase(nonConstThis, where);
	return nonConstThis;
}

/*
    Functie ce ne intoarce matricea cu pozitiile unde putem realiza operatia
    de deiteration. Ne folosim de functiile get_paths_to pentru a obtine
    path-urile care ne permit aplicarea operatiei de deiteration.
*/

std::vector<std::vector<int> > AEGraph::possible_deiterations() const {
    std::vector<std::vector<int>>::iterator it;
    std::vector<std::vector<int>> paths;

    for (int i = 0 ; i < num_subgraphs() ; ++i) {
        for (int j = 0 ; j < num_atoms() ; ++j) {
            AEGraph first_aeg = subgraphs[i];
            std::string atoms_aeg = atoms[j];

            if (first_aeg.contains(atoms_aeg)) {
                std::vector<std::vector<int>> temp =
                    first_aeg.get_paths_to(atoms_aeg);

                for (std::vector<int> &aux : temp) {
                    aux.insert(aux.begin(), i);
                }

                for (it = temp.begin() ; it != temp.end() ; ++it) {
                    paths.insert(paths.begin(), *it);
                }
            }
        }

        for (int j = 0 ; j < num_subgraphs() ; ++j) {
            AEGraph first_aeg = subgraphs[i], second_aeg = subgraphs[j];

            if (first_aeg.contains(second_aeg)) {
                std::vector<std::vector<int>> temp =
                    first_aeg.get_paths_to(second_aeg);

                for (std::vector<int> &aux : temp) {
                    aux.insert(aux.begin(), i);
                }

                for (it = temp.begin() ; it != temp.end() ; ++it) {
                    paths.insert(paths.begin(), *it);
                }
            }
        }
    }

    return paths;
}

/*
    Functie ce realizeaza operatia de deiterate, similara cu erase asa ca
    doar am folosit erase-ul pentru a evita codul duplicat.
*/

AEGraph AEGraph::deiterate(std::vector<int> where) const {
    return erase(where);
}
