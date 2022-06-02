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

	if(argc<4){
		printf("%s db-file key value\n",argv[0]);
		return 0;
	}
	

	mdb_env_create(&env);
	mdb_env_set_maxreaders(env,1);
	mdb_env_set_mapsize(env, 10485760);
	mdb_env_open(env,argv[1], MDB_FIXEDMAP|MDB_NOSUBDIR,0664);
	mdb_txn_begin(env, NULL, 0, &txn);
	mdb_dbi_open(txn, NULL, 0, &dbi);

	key.mv_data = argv[2];
	key.mv_size = strlen(argv[2]);
	
	data.mv_data = argv[3];
	data.mv_size = strlen(argv[3]);

	mdb_put(txn, dbi, &key, &data, MDB_NOOVERWRITE);
	mdb_txn_commit(txn);
	mdb_dbi_close(env,dbi);
	mdb_env_close(env);

	return 0;
}
