#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <string>
/* uncomment for applications that use vectors */
/*#include <vector>*/

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <curses.h>

#define EXAMPLE_HOST "13.59.193.177"
#define EXAMPLE_USER "test1"
#define EXAMPLE_PASS "test1"
#define EXAMPLE_DB "mmo"

using namespace std;
void draw_borders(WINDOW *screen) {
  int x, y, i;
  getmaxyx(screen, y, x); // 4 corners
  mvwprintw(screen, 0, 0, "+");
  mvwprintw(screen, y - 1, 0, "+");
  mvwprintw(screen, 0, x - 1, "+");
  mvwprintw(screen, y - 1, x - 1, "+"); // sides
  for (i = 1; i < (y - 1); i++) {
    mvwprintw(screen, i, 0, "|");
    mvwprintw(screen, i, x - 1, "|");
  } // top and bottom
  for (i = 1; i < (x - 1); i++) {
    mvwprintw(screen, 0, i, "-");
    mvwprintw(screen, y - 1, i, "-");
  }
}

int main(int argc, const char **argv) {
  string url(argc >= 2 ? argv[1] : EXAMPLE_HOST);
  const string user(argc >= 3 ? argv[2] : EXAMPLE_USER);
  const string pass(argc >= 4 ? argv[3] : EXAMPLE_PASS);
  const string database(argc >= 5 ? argv[4] : EXAMPLE_DB);

  cout << "Connecting to game server..." << endl;
  cout << endl;

  int cursor_x, cursor_y, item_x, item_y;
  string usr(argv[2]);
  vector<string> cont_vector;
  cont_vector.push_back(usr);
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  WINDOW *win = newwin(20, 50, 0, 0);
  WINDOW *text = newwin(20, 25, 0, 51);
  WINDOW *win_hp = newwin(5, 20, 21, 0);
  WINDOW *inv = newwin(5, 20, 21, 31);

  scrollok(text, TRUE);
  keypad(stdscr, TRUE);

  try {
    // connector initialize
    sql::Driver *driver = get_driver_instance();
    std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    con->setSchema(database);
    std::auto_ptr<sql::Statement> stmt(con->createStatement());

    for (;;) {
      int ch = getch();

      // check input
      if (ch == KEY_UP) {
        wclear(win);
        wclear(text);
		stmt->execute("CALL moveup('test1', @x, @y)");
		 std::auto_ptr<sql::ResultSet> res(
		 stmt->executeQuery("SELECT @x AS pos_x, @y AS pos_y"));
		 while (res->next()) {
		 string posx = res->getString("pos_x");
		 string posy = res->getString("pos_y");
		 char *cx = &posx[0];
		 char *cy = &posy[0];
		 wprintw(text, "You're at (%s,%s)", cx, cy);
		}
        /*std::auto_ptr<sql::PreparedStatement> pstmt;*/
        //std::auto_ptr<sql::ResultSet> res;

        //pstmt.reset(con->prepareStatement("CALL moveup(?,@x,@y)"));

        //pstmt->setString(1, cont_vector[0]);
        //pstmt->execute();
        //res.reset(pstmt->executeQuery("SELECT @x AS pos_x, @y AS pos_y"));
        //while (res->next()) {
          //string posx = res->getString("pos_x");
          //string posy = res->getString("pos_y");
          //char *cx = &posx[0];
          //char *cy = &posy[0];
          //wprintw(text, "You're at (%s,%s)", cx, cy);
        /*}*/

        wmove(win, cursor_y - 1, cursor_x);
        waddch(win, '@');
        draw_borders(win);
        cursor_y -= 1;

        wrefresh(text);

      } else if (ch == KEY_DOWN) {
        wclear(win);
        wclear(text);
        stmt->execute("CALL movedown('test1', @x, @y)");
        std::auto_ptr<sql::ResultSet> res(
            stmt->executeQuery("SELECT @x AS pos_x, @y AS pos_y"));
        while (res->next()) {
          string posx = res->getString("pos_x");
          string posy = res->getString("pos_y");
          char *cx = &posx[0];
          char *cy = &posy[0];
          wprintw(text, "You're at (%s,%s)", cx, cy);
        }
        wmove(win, cursor_y + 1, cursor_x);
        waddch(win, '@');
        draw_borders(win);
        cursor_y += 1;
        wrefresh(text);

      } else if (ch == KEY_LEFT) {
        wclear(win);
        wclear(text);
        stmt->execute("CALL moveleft('test1', @x, @y)");
        std::auto_ptr<sql::ResultSet> res(
            stmt->executeQuery("SELECT @x AS pos_x, @y AS pos_y"));
        while (res->next()) {
          string posx = res->getString("pos_x");
          string posy = res->getString("pos_y");
          char *cx = &posx[0];
          char *cy = &posy[0];
          wprintw(text, "You're at (%s,%s)", cx, cy);
        }
        wmove(win, cursor_y, cursor_x - 1);
        waddch(win, '@');
        draw_borders(win);
        cursor_x -= 1;

        wrefresh(text);

      } else if (ch == KEY_RIGHT) {
        wclear(win);
        wclear(text);
        stmt->execute("CALL moveright('test1', @x, @y)");
        std::auto_ptr<sql::ResultSet> res(
            stmt->executeQuery("SELECT @x AS pos_x, @y AS pos_y"));
        while (res->next()) {
          string posx = res->getString("pos_x");
          string posy = res->getString("pos_y");
          char *cx = &posx[0];
          char *cy = &posy[0];
          wprintw(text, "You're at (%s,%s)", cx, cy);
        }
        wmove(win, cursor_y, cursor_x + 1);
        waddch(win, '@');
        draw_borders(win);
        cursor_x += 1;

        wrefresh(text);
      } else {
        wclear(win);
        wclear(text);
        wclear(win_hp);
        wclear(inv);

        stmt->execute("CALL get_info('test1', @time, @hp, @room, @x, @y)");
        std::auto_ptr<sql::ResultSet> res(
            stmt->executeQuery("SELECT @time as logintime, @hp as hp, @room as "
                               "inroom, @x AS pos_x, @y AS pos_y"));
        while (res->next()) {
          string logintime = res->getString("logintime");
          string hp = res->getString("hp");
          string inroom = res->getString("inroom");
          string posx = res->getString("pos_x");
          string posy = res->getString("pos_y");
          char *clogintime = &logintime[0];
          char *chp = &hp[0];
          char *cinroom = &inroom[0];
          char *cx = &posx[0];
          char *cy = &posy[0];
          wprintw(text, "You're at (%s,%s)\n", cx, cy);
          wprintw(win_hp, "HP: %s\t%s Time: %s", chp, cinroom, clogintime);
		  wprintw(inv, "Inventory");
          cursor_y = stoi(posy);
          cursor_x = stoi(posx);
        }
        stmt->execute("CALL displayitem('test1')");
        do {
          res.reset(stmt->getResultSet());
          while (res->next()) {
            string itemname = res->getString("itemname");
            string itemposx = res->getString("itemx");
            string itemposy = res->getString("itemy");
            char *citemname = &itemname[0];
            char *citemposx = &itemposx[0];
            char *citemposy = &itemposy[0];
            wprintw(text, "A %s is at (%s,%s)\n", citemname, citemposx,
                    citemposy);
          item_x = stoi(itemposx);
          item_y = stoi(itemposy);
          wmove(win, item_y, item_x);
          waddch(win, 'A');
		  }
        } while (stmt->getMoreResults());

stmt->execute("CALL showplayers('test1')");
        do {
          res.reset(stmt->getResultSet());
          while (res->next()) {
            string playername = res->getString("playerid");
            string playerposx = res->getString("positionx");
            string playerposy = res->getString("positiony");
            char *cplayername = &playername[0];
            char *cplayerposx = &playerposx[0];
            char *cplayerposy = &playerposy[0];
            wprintw(text, "A %s is at (%s,%s)\n", cplayername, cplayerposx,
                    cplayerposy);
          item_x = stoi(playerposx);
          item_y = stoi(playerposy);
          wmove(win, item_y, item_x);
          waddch(win, 'O');
		  }
        } while (stmt->getMoreResults());



        wmove(win, cursor_y, cursor_x);
        waddch(win, '@');
        draw_borders(win);
        wrefresh(text);
        wrefresh(win_hp);
		wrefresh(inv);
      }
      wrefresh(win);
    }

    /*    sql::Driver *driver = get_driver_instance();*/
    // std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
    // con->setSchema(database);
    // std::auto_ptr<sql::Statement> stmt(con->createStatement());

    // stmt->execute("CALL moveleft('test1', @x, @y)");
    // std::auto_ptr<sql::ResultSet> res(
    // stmt->executeQuery("SELECT @x AS pos_x, @y AS pos_y"));
    // while (res->next())
    // cout << "You're now at (" << res->getString("pos_x") << ", "
    /*<< res->getString("pos_y") << ")" << endl;*/

  } catch (sql::SQLException &e) {
    /*
     *MySQL Connector/C++ throws three different exceptions:
     *
     *- sql::MethodNotImplementedException (derived from sql::SQLException)
     *- sql::InvalidArgumentException (derived from sql::SQLException)
     *- sql::SQLException (derived from std::runtime_error)
     */
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    /* what() (derived from std::runtime_error) fetches error message */
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    endwin();
    return EXIT_FAILURE;
  }

  cout << "Done." << endl;
  endwin();
  return EXIT_SUCCESS;
}
