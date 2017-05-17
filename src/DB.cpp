/*
 *
 * (C) 2013-17 - ntop.org
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#include "ntop_includes.h"

/* ******************************************* */

DB::DB(NetworkInterface *_iface) {
  if((m = new(std::nothrow) Mutex()) == NULL)
    ntop->getTrace()->traceEvent(TRACE_WARNING, "Internal error: NULL mutex. Are you running out of memory?");

  iface = _iface;
}

/* ******************************************* */

DB::~DB() {
  if(m) delete m;
}

/* ******************************************* */

bool DB::dumpFlow(time_t when, Flow *f, char *json) {
<<<<<<< HEAD
  ntop->getTrace()->traceEvent(TRACE_WARNING, "Internal error");
  return(false);
=======
  const char *create_flows_db = "BEGIN; CREATE TABLE IF NOT EXISTS flows (ID INTEGER PRIMARY KEY   AUTOINCREMENT, vlan_id number, cli_ip string KEY, cli_port number, "
    "srv_ip string KEY, srv_port number, proto number, bytes number, first_seen number, last_seen number, duration number, json string);";
  char sql[4096], cli_str[64], srv_str[64];
  sqlite3_stmt *stmt = NULL;
  char *j = json ? json : (char*)"";
  bool rc = true;
  int int_rc;

  snprintf(sql, sizeof(sql),
	   "INSERT INTO flows VALUES (NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");

  ntop->getTrace()->traceEvent(TRACE_DEBUG, "Dump Flow: %s", json);

  if(m) m->lock(__FILE__, __LINE__);
  initDB(when, create_flows_db);

  if((db == NULL) || (f->get_cli_host() == NULL) || (f->get_srv_host() == NULL))
    goto out;

  if (sqlite3_prepare(db, sql, -1, &stmt, 0) ||
      sqlite3_bind_int(stmt, 1, f->get_vlan_id()) ||
      sqlite3_bind_text(stmt, 2, f->get_cli_host()->get_ip()->print(cli_str, sizeof(cli_str)), sizeof(cli_str), SQLITE_TRANSIENT) ||
      sqlite3_bind_int(stmt, 3, f->get_cli_port()) ||
      sqlite3_bind_text(stmt, 4, f->get_srv_host()->get_ip()->print(srv_str, sizeof(srv_str)), sizeof(srv_str), SQLITE_TRANSIENT) ||
      sqlite3_bind_int(stmt, 5, f->get_srv_port()) ||
      sqlite3_bind_int(stmt, 6,  f->get_protocol()) ||
      sqlite3_bind_int(stmt, 7, (unsigned long)f->get_bytes()) ||
      sqlite3_bind_int(stmt, 8, (unsigned) f->get_first_seen()) ||
      sqlite3_bind_int(stmt, 9, (unsigned) f->get_last_seen()) ||
      sqlite3_bind_int(stmt, 10, f->get_duration()) ||
      sqlite3_bind_text(stmt, 11, j, strlen(j), SQLITE_TRANSIENT)) {
    ntop->getTrace()->traceEvent(TRACE_ERROR, "[DB] Dump Flow query build failed: %s", sqlite3_errmsg(db));
    rc = false;
    goto out;
  }

  while((int_rc = sqlite3_step(stmt)) != SQLITE_DONE) {
    if(int_rc == SQLITE_ERROR) {
      ntop->getTrace()->traceEvent(TRACE_INFO, "[DB] SQL Error: step");
      rc = false;
      goto out;
    }
  }

out:
  if (stmt) sqlite3_finalize(stmt);
  if(m) m->unlock(__FILE__, __LINE__);

  return rc;
>>>>>>> dc3872b88c463aa5e5ba333fd357c8641f72c283
}

/* ******************************************* */

int DB::exec_sql_query(lua_State *vm, char *sql, bool limit_rows, bool wait_for_db_created) {
  ntop->getTrace()->traceEvent(TRACE_WARNING, "Internal error");
  return(false);
}

/* ******************************************* */

void DB::startDBLoop() {
  ntop->getTrace()->traceEvent(TRACE_WARNING, "Internal error");
}
