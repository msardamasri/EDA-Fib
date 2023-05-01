#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Factores_v12


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

    typedef vector<int> int_vec;
    typedef vector <bool> bool_vec;
    typedef vector <bool_vec> bool_matrix;

    //moviment segons el command
    void movex(int id, char mv) {
        if (mv == 'B') command(id, Bottom);
        else if (mv == 'L') command(id, Left);
        else if (mv == 'R') command(id, Right);
        else if (mv == 'T') command(id, Top);
        else if (mv == 'Z') command(id, TL);
        else if (mv == 'Y') command(id, BR);
        else if (mv == 'U') command(id, RT);
        else if (mv == 'P') command(id, LB);
    }

    //moviment invers el command
    void movey(int id, char mv) {
        if (mv == 'B') command(id, Top);
        else if (mv == 'L') command(id, Right);
        else if (mv == 'R') command(id, Left);
        else if (mv == 'T') command(id, Bottom);
        else if (mv == 'Z') command(id, BR);
        else if (mv == 'Y') command(id, TL);
        else if (mv == 'U') command(id, LB);
        else if (mv == 'P') command(id, RT);
    }
  
    //bfs per buscar enemics sense parets
    pair<char, int> conquer_nowall(int id) {
        bool_matrix visited(rows(), bool_vec(cols(), false));
        Unit u = unit(id);
        int dist = -1;
        queue<pair<Pos, pair<char, int>>> q; 
        q.push({{u.pos}, {'X', 0}});
        visited[u.pos.i][u.pos.j] = true;
        Pos ini = q.front().first;
        for (int i = 0; i < 8; ++i) {
            char dr;
            Pos s = ini;
            if (i == 0) {
                ++s.i;
                dr = 'B';
            }
            else if (i == 1) {
                --s.i;
                --s.j;
                dr = 'Z';
            }
            else if (i == 2) {
                ++s.j;
                ++s.i;
                dr = 'Y';
            }
            else if (i == 3) {
                ++s.j;
                --s.i;
                dr = 'U';
            }
            else if (i == 4) {
                --s.j;
                ++s.i;
                dr = 'P';
            }
            else if (i == 5) {
                --s.i;
                dr = 'T';
            }
            else if (i == 6) {
                ++s.j;
                dr = 'R';
            }
            else {
                --s.j;
                dr = 'L';
            }
            Cell c;
            if (pos_ok(s)) c = cell(s);
            if (pos_ok(s) and not visited[s.i][s.j] and c.type != Granite and c.type != Abyss and c.type != Rock) {
               if (c.id == -1) {
                    q.push({s, {dr,1}});
                    visited[s.i][s.j] = true;
                }
                if (c.id != -1 and unit(c.id).player != me()) return {dr, 1};
            }
        }
        while (!q.empty()) {
            Pos actual = q.front().first;
            pair<char, int> d = q.front().second;
            char x = q.front().second.first;
            dist = d.second+1;
            q.pop();
            Cell c = cell(actual);
            if (c.type == Cave and c.owner != me()) return d;
            for (int i = 0; i < 8; ++i) {
                Pos s = actual;
                if (i == 0) ++s.i;
                else if (i == 1) --s.i;
                else if (i == 2) ++s.j;
                else if (i == 3) --s.j;
                else if (i == 4) {
                    ++s.i;
                    ++s.j;
                }
                else if (i == 5) {
                    --s.i;
                    --s.j;
                }
                else if (i == 6) {
                    ++s.i;
                    --s.j;
                }
                else {
                    ++s.j;
                    --s.i;
                }
                Cell c;
                if (pos_ok(s)) c = cell(s);
                if (pos_ok(s) and not visited[s.i][s.j] and c.type != Granite and c.type != Abyss and c.type != Rock) {
                    if(c.type == Rock) {
                        q.push({s, {x, dist}});
                        visited[s.i][s.j] = true;
                    }
                    else {
                        q.push({s, {x, dist + 1}});
                        visited[s.i][s.j] = true;
                    }
                }
            }
        }
        return {'X', 4000};
    }

    //bfs per buscar enemics per la roca tambe
    pair<char, int> conquer_wall(int id) {
        bool_matrix visited(rows(), bool_vec(cols(), false));
        Unit u = unit(id);
        int dist = -1;
        queue<pair<Pos, pair<char, int>>> q; 
        q.push({{u.pos}, {'X', 0}});
        visited[u.pos.i][u.pos.j] = true;
        Pos ini = q.front().first;
        for (int i = 0; i < 8; ++i) {
            char dr;
            Pos s = ini;
            if (i == 0) {
                ++s.i;
                dr = 'B';
            }
            else if (i == 1) {
                --s.i;
                --s.j;
                dr = 'Z';
            }
            else if (i == 2) {
                ++s.j;
                ++s.i;
                dr = 'Y';
            }
            else if (i == 3) {
                ++s.j;
                --s.i;
                dr = 'U';
            }
            else if (i == 4) {
                --s.j;
                ++s.i;
                dr = 'P';
            }
            else if (i == 5) {
                --s.i;
                dr = 'T';
            }
            else if (i == 6) {
                ++s.j;
                dr = 'R';
            }
            else {
                --s.j;
                dr = 'L';
            }
            Cell c;
            if (pos_ok(s)) c = cell(s);
            if (pos_ok(s) and not visited[s.i][s.j] and c.type != Granite and c.type != Abyss) {
               if (c.id == -1) {
                    q.push({s, {dr,1}});
                    visited[s.i][s.j] = true;
                }
                if (c.id != -1 and unit(c.id).player != me()) return {dr, 1};
            }
        }
        while (!q.empty()) {
            Pos actual = q.front().first;
            pair<char, int> d = q.front().second;
            char x = q.front().second.first;
            dist = d.second+1;
            q.pop();
            Cell c = cell(actual);
            if (c.type == Cave and c.owner != me()) return d;
            for (int i = 0; i < 8; ++i) {
                Pos s = actual;
                if (i == 0) ++s.i;
                else if (i == 1) --s.i;
                else if (i == 2) ++s.j;
                else if (i == 3) --s.j;
                else if (i == 4) {
                    ++s.i;
                    ++s.j;
                }
                else if (i == 5) {
                    --s.i;
                    --s.j;
                }
                else if (i == 6) {
                    ++s.i;
                    --s.j;
                }
                else {
                    ++s.j;
                    --s.i;
                }
                Cell c;
                if (pos_ok(s)) c = cell(s);
                if (pos_ok(s) and not visited[s.i][s.j] and c.type != Granite and c.type != Abyss) {
                    if(c.type == Rock) {
                        q.push({s, {x, dist + c.turns}});
                        visited[s.i][s.j] = true;
                    }
                    else {
                        q.push({s, {x, dist + 1}});
                        visited[s.i][s.j] = true;
                    }
                }
            }
        }
        return {'X', 4000};
    }
    
    //bfs per seguir els enanos
    char seguir(int id) {
        bool_matrix visited(rows(), bool_vec(cols(), false));
        Unit u = unit(id);
        queue<pair<Pos, char>> q; 
        q.push({{u.pos}, 'X'});
        visited[u.pos.i][u.pos.j] = true;
        Pos ini = q.front().first;
        for (int i = 0; i < 4; ++i) {
            char dr;
            Pos s = ini;
            if (i == 0) {
                ++s.i;
                dr = 'B';
            }
            else if (i == 1) {
                --s.i;
                dr = 'T';
            }
            else if (i == 2) {
                ++s.j;
                dr = 'R';
            }
            else {
                --s.j;
                dr = 'L';
            }
            Cell c;
            if (pos_ok(s)) c = cell(s);
            if (pos_ok(s) and not visited[s.i][s.j] and (c.type == Cave or c.type == Outside)) {
                if (c.id == -1) {
                    q.push({s, dr});
                    visited[s.i][s.j] = true;
                }
            }
        }
        while (!q.empty()) {
            Pos actual = q.front().first;
            char d = q.front().second;
            q.pop();
            Cell c = cell(actual);
            if (c.id != -1) {
                Unit u = unit(c.id);
                if (u.type == Dwarf and u.player == me()) return d;
            }
            for (int i = 0; i < 4; ++i) {
                Pos s = actual;
                if (i == 0) ++s.i;
                else if (i == 1) --s.i;
                else if (i == 2) ++s.j;
                else --s.j;
                Cell c;
                if (pos_ok(s)) c = cell(s);
                if (pos_ok(s) and not visited[s.i][s.j] and (c.type == Cave or c.type == Outside)) {
                    q.push({s, d});
                    visited[s.i][s.j] = true;
                }
            }
        }
        return 'X';
    }

    //bfs enano to blrg
    char to_balrog(int id) {
        bool_matrix visited(rows(), bool_vec(cols(), false));
        Unit u = unit(id);
        queue<pair<Pos, char>> q; 
        q.push({{u.pos}, 'X'});
        visited[u.pos.i][u.pos.j] = true;
        Pos ini = q.front().first;
        for (int i = 0; i < 8; ++i) {
            char dr;
            Pos s = ini;
            if (i == 0) {
                ++s.i;
                dr = 'B';
            }
            else if (i == 1) {
                --s.i;
                --s.j;
                dr = 'Z';
            }
            else if (i == 2) {
                ++s.j;
                ++s.i;
                dr = 'Y';
            }
            else if (i == 3) {
                ++s.j;
                --s.i;
                dr = 'U';
            }
            else if (i == 4) {
                --s.j;
                ++s.i;
                dr = 'P';
            }
            else if (i == 5) {
                --s.i;
                dr = 'T';
            }
            else if (i == 6) {
                ++s.j;
                dr = 'R';
            }
            else {
                --s.j;
                dr = 'L';
            }
            Cell c;
            if (pos_ok(s)) c = cell(s);
            if (pos_ok(s) and not visited[s.i][s.j] and c.type != Granite) {
                if (c.id == -1) {
                    q.push({s, dr});
                    visited[s.i][s.j] = true;
                }
                if (c.id != -1 and unit(c.id).player != me()) return dr;
            }
        }
        while (!q.empty()) {
            Pos actual = q.front().first;
            char d = q.front().second;
            q.pop();
            Cell c = cell(actual);
            if (c.id != -1) {
                Unit u = unit(c.id);
                if (u.type == Balrog) return d;
            }
            for (int i = 0; i < 8; ++i) {
                Pos s = actual;
                if (i == 0) ++s.i;
                else if (i == 1) --s.i;
                else if (i == 2) ++s.j;
                else if (i == 3) --s.j;
                else if (i == 4) {
                    ++s.i;
                    ++s.j;
                }
                else if (i == 5) {
                    --s.i;
                    --s.j;
                }
                else if (i == 6) {
                    ++s.i;
                    --s.j;
                }
                else {
                    ++s.j;
                    --s.i;
                }
                Cell c;
                if (pos_ok(s)) c = cell(s);
                if (pos_ok(s) and not visited[s.i][s.j] and c.type != Granite) {
                    q.push({s, d});
                    visited[s.i][s.j] = true;
                }
            }
        }
        return 'X';
    }

    //bfs per buscar enemics sense parets
    pair<char, int> enemic_dist_nowall(int id) {
        bool_matrix visited(rows(), bool_vec(cols(), false));
        Unit u = unit(id);
        int dist = -1;
        queue<pair<Pos, pair<char, int>>> q; 
        q.push({{u.pos}, {'X', 0}});
        visited[u.pos.i][u.pos.j] = true;
        Pos ini = q.front().first;
        for (int i = 0; i < 8; ++i) {
            char dr;
            Pos s = ini;
            if (i == 0) {
                ++s.i;
                dr = 'B';
            }
            else if (i == 1) {
                --s.i;
                --s.j;
                dr = 'Z';
            }
            else if (i == 2) {
                ++s.j;
                ++s.i;
                dr = 'Y';
            }
            else if (i == 3) {
                ++s.j;
                --s.i;
                dr = 'U';
            }
            else if (i == 4) {
                --s.j;
                ++s.i;
                dr = 'P';
            }
            else if (i == 5) {
                --s.i;
                dr = 'T';
            }
            else if (i == 6) {
                ++s.j;
                dr = 'R';
            }
            else {
                --s.j;
                dr = 'L';
            }
            Cell c;
            if (pos_ok(s)) c = cell(s);
            if (pos_ok(s) and not visited[s.i][s.j] and c.type != Granite and c.type != Abyss and c.type != Rock) {
               if (c.id == -1) {
                    q.push({s, {dr,1}});
                    visited[s.i][s.j] = true;
                }
                if (c.id != -1 and unit(c.id).player != me()) return {dr, 1};
            }
        }
        while (!q.empty()) {
            Pos actual = q.front().first;
            pair<char, int> d = q.front().second;
            char x = q.front().second.first;
            dist = d.second+1;
            q.pop();
            Cell c = cell(actual);
            if (c.id != -1) {
                Unit u = unit(c.id);
                if ((u.type == Dwarf or u.type == Wizard) and u.player != me()) return d;
            }
            for (int i = 0; i < 8; ++i) {
                Pos s = actual;
                if (i == 0) ++s.i;
                else if (i == 1) --s.i;
                else if (i == 2) ++s.j;
                else if (i == 3) --s.j;
                else if (i == 4) {
                    ++s.i;
                    ++s.j;
                }
                else if (i == 5) {
                    --s.i;
                    --s.j;
                }
                else if (i == 6) {
                    ++s.i;
                    --s.j;
                }
                else {
                    ++s.j;
                    --s.i;
                }
                Cell c;
                if (pos_ok(s)) c = cell(s);
                if (pos_ok(s) and not visited[s.i][s.j] and c.type != Granite and c.type != Abyss and c.type != Rock) {
                    if(c.type == Rock) {
                        q.push({s, {x, dist}});
                        visited[s.i][s.j] = true;
                    }
                    else {
                        q.push({s, {x, dist + 1}});
                        visited[s.i][s.j] = true;
                    }
                }
            }
        }
        return {'X', 4000};
    }

    //bfs per buscar enemics per la roca tambe
    pair<char, int> enemic_dist_wall(int id) {
        bool_matrix visited(rows(), bool_vec(cols(), false));
        Unit u = unit(id);
        int dist = -1;
        queue<pair<Pos, pair<char, int>>> q; 
        q.push({{u.pos}, {'X', 0}});
        visited[u.pos.i][u.pos.j] = true;
        Pos ini = q.front().first;
        for (int i = 0; i < 8; ++i) {
            char dr;
            Pos s = ini;
            if (i == 0) {
                ++s.i;
                dr = 'B';
            }
            else if (i == 1) {
                --s.i;
                --s.j;
                dr = 'Z';
            }
            else if (i == 2) {
                ++s.j;
                ++s.i;
                dr = 'Y';
            }
            else if (i == 3) {
                ++s.j;
                --s.i;
                dr = 'U';
            }
            else if (i == 4) {
                --s.j;
                ++s.i;
                dr = 'P';
            }
            else if (i == 5) {
                --s.i;
                dr = 'T';
            }
            else if (i == 6) {
                ++s.j;
                dr = 'R';
            }
            else {
                --s.j;
                dr = 'L';
            }
            Cell c;
            if (pos_ok(s)) c = cell(s);
            if (pos_ok(s) and not visited[s.i][s.j] and c.type != Granite and c.type != Abyss) {
               if (c.id == -1) {
                    q.push({s, {dr,1}});
                    visited[s.i][s.j] = true;
                }
                if (c.id != -1 and unit(c.id).player != me()) return {dr, 1};
            }
        }
        while (!q.empty()) {
            Pos actual = q.front().first;
            pair<char, int> d = q.front().second;
            char x = q.front().second.first;
            dist = d.second+1;
            q.pop();
            Cell c = cell(actual);
            if (c.id != -1) {
                Unit u = unit(c.id);
                if ((u.type == Dwarf or u.type == Wizard) and u.player != me()) return d;
            }
            for (int i = 0; i < 8; ++i) {
                Pos s = actual;
                if (i == 0) ++s.i;
                else if (i == 1) --s.i;
                else if (i == 2) ++s.j;
                else if (i == 3) --s.j;
                else if (i == 4) {
                    ++s.i;
                    ++s.j;
                }
                else if (i == 5) {
                    --s.i;
                    --s.j;
                }
                else if (i == 6) {
                    ++s.i;
                    --s.j;
                }
                else {
                    ++s.j;
                    --s.i;
                }
                Cell c;
                if (pos_ok(s)) c = cell(s);
                if (pos_ok(s) and not visited[s.i][s.j] and c.type != Granite and c.type != Abyss) {
                    if(c.type == Rock) {
                        q.push({s, {x, dist + c.turns}});
                        visited[s.i][s.j] = true;
                    }
                    else {
                        q.push({s, {x, dist + 1}});
                        visited[s.i][s.j] = true;
                    }
                }
            }
        }
        return {'X', 4000};
    }

    //bfs per buscar tresors per la roca tambe
    pair<char, int> tresor_dist(int id) {
        bool_matrix visited(rows(), bool_vec(cols(), false));
        Unit u = unit(id);
        int dist = -1;
        queue<pair<Pos, pair<char, int>>> q; 
        q.push({{u.pos}, {'X', 0}});
        visited[u.pos.i][u.pos.j] = true;
        Pos ini = q.front().first;
        for (int i = 0; i < 8; ++i) {
            char dr;
            Pos s = ini;
            if (i == 0) {
                ++s.i;
                dr = 'B';
            }
            else if (i == 1) {
                --s.i;
                --s.j;
                dr = 'Z';
            }
            else if (i == 2) {
                ++s.j;
                ++s.i;
                dr = 'Y';
            }
            else if (i == 3) {
                ++s.j;
                --s.i;
                dr = 'U';
            }
            else if (i == 4) {
                --s.j;
                ++s.i;
                dr = 'P';
            }
            else if (i == 5) {
                --s.i;
                dr = 'T';
            }
            else if (i == 6) {
                ++s.j;
                dr = 'R';
            }
            else {
                --s.j;
                dr = 'L';
            }
            Cell c;
            if (pos_ok(s)) c = cell(s);
            if (pos_ok(s) and not visited[s.i][s.j] and c.type != Granite and c.type != Abyss) {
               if (c.id == -1) {
                    q.push({s, {dr,1}});
                    visited[s.i][s.j] = true;
                }
                if (c.id != -1 and unit(c.id).player != me()) return {dr, 1};
            }
        }
        while (!q.empty()) {
            Pos actual = q.front().first;
            pair<char, int> d = q.front().second;
            char x = q.front().second.first;
            dist = d.second+1;
            q.pop();
            Cell c = cell(actual);
            if (c.treasure) return d;
            for (int i = 0; i < 8; ++i) {
                Pos s = actual;
                if (i == 0) ++s.i;
                else if (i == 1) --s.i;
                else if (i == 2) ++s.j;
                else if (i == 3) --s.j;
                else if (i == 4) {
                    ++s.i;
                    ++s.j;
                }
                else if (i == 5) {
                    --s.i;
                    --s.j;
                }
                else if (i == 6) {
                    ++s.i;
                    --s.j;
                }
                else {
                    ++s.j;
                    --s.i;
                }
                Cell c;
                if (pos_ok(s)) c = cell(s);
                if (pos_ok(s) and not visited[s.i][s.j] and c.type != Granite and c.type != Abyss) {
                    if(c.type == Rock) {
                        q.push({s, {x, dist + c.turns}});
                        visited[s.i][s.j] = true;
                    }
                    else {
                        q.push({s, {x, dist + 1}});
                        visited[s.i][s.j] = true;
                    }
                }
            }
        }
        return {'X', 4000};
    }

    //retorna la posicio del balrog
    Pos found_balrog() {
        int id = balrog_id();
        return unit(id).pos;
    }

    //mou els enanos
    void move_dwarves(const Pos& p) {
        int_vec Dwrf = dwarves(me());
        int sized = Dwrf.size();
        //moviments dels enanos
        for (int i = 0; i < sized; ++i) {
            int id = Dwrf[i];
            char mv = 'X';

            //BALROG
            Unit u = unit(id);
            int is = p.i - u.pos.i;
            int js = p.j - u.pos.j;
            //Baries
            pair<char, int> ew = enemic_dist_wall(id);
            pair<char, int> noew = enemic_dist_nowall(id);
            pair<char, int> t = tresor_dist(id);
            pair<char, int> cnw = conquer_nowall(id);
            pair<char, int> cw = conquer_wall(id);
            //holaqase
            //si la distancia fins al balrog es inferior a 8 caselles
            if (is < 6 and is > -6 and js < 6 and js > -6) {
                mv = to_balrog(id);
                //moviment invers del bfs al balrog
                movey(id, mv);
            }
            else if (sized < 55) {
                if (noew.second <= ew.second) mv = noew.first;
                else mv = ew.first;
                movex(id, mv);
            }
            else if (nb_treasures(me()) < 20 and (t.second <= ew.second or t.second <= noew.second)) movex(id, t.first);
            else if (nb_treasures(me()) < 20 and noew.second <= ew.second) movex(id, noew.first);
            else if (nb_treasures(me()) < 20 and noew.second > ew.second) movex(id, ew.first);
            else if (nb_cells(me()) < 850){
                if (cnw.second < cw.second) mv = cnw.first;
                else mv = cw.first;
                movex(id, mv);
            }
            else if ((t.second <= ew.second or t.second <= noew.second)) movex(id, t.first);
            else if (noew.second <= ew.second) movex(id, noew.first);
            else if (noew.second > ew.second) movex(id, ew.first);
        }
    }

    //mou els magos
    void move_wizards() {
        int_vec W = wizards(me());
        int sizew = W.size();
        //moviment del magos
        for (int j = 0; j < sizew; ++j) {
            int id = W[j];
            char mv = 'X';
            mv = seguir(id);
            movex(id, mv);
        }
    }

    //play function
    virtual void play () {
        Pos p = found_balrog();
        move_dwarves(p);
        move_wizards();
    }

};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);