#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lmdb.h"

int main(int argc, char * argv[])
{
	MDB_env *env;
	MDB_dbi dbi;
	MDB_val key, data;
	MDB_txn *txn;
	MDB_stat mst;
	MDB_cursor *cursor, *cur2;
	MDB_cursor_op op;
	int rc;

	if(argc<2){
		printf("%s db-file\n",argv[0]);
		return 0;
	}
	

	mdb_env_create(&env);
	mdb_env_set_maxreaders(env,1);
	mdb_env_set_mapsize(env, 10485760);
	mdb_env_open(env,argv[1], MDB_FIXEDMAP|MDB_NOSUBDIR,0664);
	mdb_txn_begin(env, NULL, MDB_RDONLY, &txn);
	mdb_dbi_open(txn, NULL, 0, &dbi);
	mdb_cursor_open(txn, dbi, &cursor);
	while((rc=mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
		printf("key: %.*s, data: %.*s\n",
			(int)key.mv_size, (char *)key.mv_data,
			(int)data.mv_size,(char *)data.mv_data);
	}
	mdb_cursor_close(cursor);

	mdb_put(txn, dbi, &key, &data, MDB_NOOVERWRITE);
	mdb_txn_abort(txn);
	mdb_dbi_close(env,dbi);
	mdb_env_close(env);

	return 0;
}
