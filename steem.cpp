#include <curl/curl.h>
#include <lua.hpp>

extern "C"
{
#define api_url "https://api.steemit.com"

typedef struct MemoryStruct {
  char *memory;
  size_t size;
}data_t;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if( mem->memory == NULL)
  {
    printf( "No enough memory to allocate\n" );
	return 0;
  }
  
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

static void easy_init( CURL** hnd, data_t* chunk )
{
  if( hnd == NULL || chunk == NULL ) return;
  
  chunk->memory = (char*)malloc(1);
  chunk->size = 0; 

  *hnd = curl_easy_init();
  curl_easy_setopt(*hnd, CURLOPT_BUFFERSIZE, 1024000L);
  curl_easy_setopt(*hnd, CURLOPT_URL, api_url);
  curl_easy_setopt(*hnd, CURLOPT_USERAGENT, "curl/7.54.1");
  curl_easy_setopt(*hnd, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(*hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
  curl_easy_setopt(*hnd, CURLOPT_TCP_KEEPALIVE, 1L);
  curl_easy_setopt(*hnd, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(*hnd, CURLOPT_WRITEDATA, (void*)chunk);
  //curl_easy_setopt(*hnd, CURLOPT_VERBOSE, 1);
  
  return;
}

static void easy_post( lua_State* l, CURL** hnd, data_t* chunk )
{
  if( hnd == NULL || chunk == NULL ) return;

  if( chunk->memory != NULL )
  {
	lua_pushstring(l, chunk->memory);
	lua_pushinteger(l, chunk->size);
		
	free( chunk->memory );
	chunk->memory = NULL;
	chunk->size = 0;
  }
  else
	printf( "No data received\n" );

  curl_easy_cleanup(*hnd);
  *hnd = NULL;
}

static int get_trending_tags_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"call\", \"params\": [\"database_api\", \"get_trending_tags\", [\"%s\",\"%d\"]], \"id\": 1}", name, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_discussions_by_trending_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* tag = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_discussions_by_trending\", \"params\": [{\"tag\":\"%s\", \"start_author\":\"%s\", \"start_permlink\":\"%s\", \"limit\": \"%d\"}], \"id\": 1}", tag, name, permlink, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_discussions_by_created_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* tag = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_discussions_by_created\", \"params\": [{\"tag\":\"%s\", \"start_author\":\"%s\", \"start_permlink\":\"%s\", \"limit\": \"%d\"}], \"id\": 1}", tag, name, permlink, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_discussions_by_active_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* tag = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_discussions_by_active\", \"params\": [{\"tag\":\"%s\", \"start_author\":\"%s\", \"start_permlink\":\"%s\", \"limit\": \"%d\"}], \"id\": 1}", tag, name, permlink, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_discussions_by_cashout_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* tag = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_discussions_by_cashout\", \"params\": [{\"tag\":\"%s\", \"start_author\":\"%s\", \"start_permlink\":\"%s\", \"limit\": \"%d\"}], \"id\": 1}", tag, name, permlink, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_discussions_by_payout_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* tag = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_discussions_by_payout\", \"params\": [{\"tag\":\"%s\", \"start_author\":\"%s\", \"start_permlink\":\"%s\", \"limit\": \"%d\"}], \"id\": 1}", tag, name, permlink, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_discussions_by_votes_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* tag = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_discussions_by_votes\", \"params\": [{\"tag\":\"%s\", \"start_author\":\"%s\", \"start_permlink\":\"%s\", \"limit\": \"%d\"}], \"id\": 1}", tag, name, permlink, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_discussions_by_children_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* tag = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_discussions_by_children\", \"params\": [{\"tag\":\"%s\", \"start_author\":\"%s\", \"start_permlink\":\"%s\", \"limit\": \"%d\"}], \"id\": 1}", tag, name, permlink, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_discussions_by_hot_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* tag = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_discussions_by_hot\", \"params\": [{\"tag\":\"%s\", \"start_author\":\"%s\", \"start_permlink\":\"%s\", \"limit\": \"%d\"}], \"id\": 1}", tag, name, permlink, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_discussions_by_feed_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* tag = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_discussions_by_feed\", \"params\": [{\"tag\":\"%s\", \"start_author\":\"%s\", \"start_permlink\":\"%s\", \"limit\": \"%d\"}], \"id\": 1}", tag, name, permlink, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_discussions_by_blog_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* tag = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_discussions_by_blog\", \"params\": [{\"tag\":\"%s\", \"start_author\":\"%s\", \"start_permlink\":\"%s\", \"limit\": \"%d\"}], \"id\": 1}", tag, name, permlink, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_discussions_by_comments_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* tag = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_discussions_by_comments\", \"params\": [{\"tag\":\"%s\", \"start_author\":\"%s\", \"start_permlink\":\"%s\", \"limit\": \"%d\"}], \"id\": 1}", tag, name, permlink, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_block_header_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int number = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_block_header\", \"params\": [\"%d\"], \"id\": 1}", number );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_block_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int number = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_block\", \"params\": [\"%d\"], \"id\": 1}", number );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_state_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  const char* path = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_state\", \"params\": [\"%d\"], \"id\": 1}", path );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_config_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"jsonrpc\": \"2.0\", \"method\": \"get_config\", \"params\": [[]], \"id\": 1}");
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)67);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_dynamic_global_properties_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"jsonrpc\": \"2.0\", \"method\": \"get_dynamic_global_properties\", \"params\": [[]], \"id\": 1}");
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)86);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_chain_properties_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"jsonrpc\": \"2.0\", \"method\": \"get_chain_properties\", \"params\": [[]], \"id\": 1}");
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)77);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_feed_history_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"jsonrpc\": \"2.0\", \"method\": \"get_feed_history\", \"params\": [[]], \"id\": 1}");
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)73);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_current_median_history_price_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"jsonrpc\": \"2.0\", \"method\": \"get_current_median_history_price\", \"params\": [[]], \"id\": 1}");
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)89);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_hardfork_version_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"jsonrpc\": \"2.0\", \"method\": \"get_hardfork_version\", \"params\": [[]], \"id\": 1}");
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)77);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_next_scheduled_hardfork_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"jsonrpc\": \"2.0\", \"method\": \"get_next_scheduled_hardfork\", \"params\": [[]], \"id\": 1}");
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)84);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_reward_fund_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_reward_fund\", \"params\": [\"%s\"], \"id\": 1}", name );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_vesting_delegations_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* from = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* account = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_vesting_delegations\", \"params\": [\"%s\",\"%s\",\"%d\"], \"id\": 1}", account, from, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_key_references_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  const char* key = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"call\", \"params\": [\"account_by_key_api\", \"get_key_references\", [[\"%s\"]]], \"id\": 1}", key );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_accounts_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_accounts\", \"params\": [[\"%s\"]], \"id\": 1}", name );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_account_references_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int id = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_account_references\", \"params\": [\"%d\"], \"id\": 1}", id );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int lookup_account_names_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"lookup_account_names\", \"params\": [[\"%s\"]], \"id\": 1}", name );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int lookup_accounts_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"call\", \"params\": [\"database_api\", \"lookup_accounts\", [\"%s\",\"%d\"]], \"id\": 1}", name, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_account_count_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"jsonrpc\": \"2.0\", \"method\": \"call\", \"params\": [\"database_api\", \"get_account_count\", [\"\"]], \"id\": 1}");
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)100);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_conversion_requests_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_conversion_requests\", \"params\": [\"%s\"], \"id\": 1}", name );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_account_history_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  int from = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_account_history\", \"params\": [\"%s\",\"%d\",\"%d\"], \"id\": 1}", name, from, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_recovery_request_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_recovery_request\", \"params\": [\"%s\"], \"id\": 1}", name );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_order_book_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_order_book\", \"params\": [\"%d\"], \"id\": 1}", limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_open_orders_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );

  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_open_orders\", \"params\": [\"%s\"], \"id\": 1}", name );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_liquidity_queue_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_liquidity_queue\", \"params\": [\"%s\",\"%d\"], \"id\": 1}", name, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_transaction_hex_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int trx = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_transaction_hex\", \"params\": [{\"trx\":\"%d\"}], \"id\": 1}", trx );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_transaction_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int trx = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_transaction\", \"params\": [\"%d\"], \"id\": 1}", trx );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_required_signatures_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int trx = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* key = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_required_signatures\", \"params\": [{\"trx\":\"%d\"},[\"%s\"]], \"id\": 1}", trx, key );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_potential_signatures_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int trx = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_potential_signatures\", \"params\": [{\"trx\":\"%d\"}], \"id\": 1}", trx );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int verify_authority_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int trx = lua_tonumber(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"verify_authority\", \"params\": [{\"trx\":\"%d\"}], \"id\": 1}", trx );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int verify_account_authority_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* key = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"verify_account_authority\", \"params\": [\"%s\",[\"%s\"]], \"id\": 1}", name, key );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_active_votes_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_active_votes\", \"params\": [\"%s\",\"%s\"], \"id\": 1}", name, permlink );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_account_votes_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_account_votes\", \"params\": [\"%s\"], \"id\": 1}", name );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  if( ret != CURLE_OK )
  {
	const char *str = curl_easy_strerror( ret );
	printf("libcurl said %s\n", str);
  }

  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_content_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_content\", \"params\": [\"%s\",\"%s\"], \"id\": 1}", name, permlink );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_content_replies_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_content_replies\", \"params\": [\"%s\",\"%s\"], \"id\": 1}", name, permlink );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_discussions_by_author_before_date_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tointeger(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* time = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_discussions_by_author_before_date\", \"params\": [\"%s\",\"%s\",\"%s\",\"%d\"], \"id\": 1}", name, permlink, time, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_replies_by_last_update_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tointeger(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* permlink = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_replies_by_last_update\", \"params\": [\"%s\",\"%s\",\"%d\"], \"id\": 1}", name, permlink, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_witnesses_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int wid = lua_tointeger(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_witnesses\", \"params\": [[\"%d\"]], \"id\": 1}", wid );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_witness_by_account_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_witness_by_account\", \"params\": [\"%s\"], \"id\": 1}", name );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_witnesses_by_vote_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tointeger(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"get_witnesses_by_vote\", \"params\": [\"%s\",%d], \"id\": 1}", name, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int lookup_witness_accounts_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tointeger(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"lookup_witness_accounts\", \"params\": [\"%s\",%d], \"id\": 1}", name, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_witness_count_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"jsonrpc\": \"2.0\", \"method\": \"get_witness_count\", \"params\": [], \"id\": 1}");
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)72);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_active_witnesses_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"jsonrpc\": \"2.0\", \"method\": \"get_active_witnesses\", \"params\": [], \"id\": 1}");
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)75);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_miner_queue_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "{\"jsonrpc\": \"2.0\", \"method\": \"get_miner_queue\", \"params\": [], \"id\": 1}");
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)70);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_followers_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tointeger(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* type = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* start = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"call\", \"params\": [\"follow_api\", \"get_followers\", [\"%s\", \"%s\", \"%s\", \"%d\"]], \"id\": 1}", name, start, type, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_following_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tointeger(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* type = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* start = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"call\", \"params\": [\"follow_api\", \"get_following\", [\"%s\", \"%s\", \"%s\", \"%d\"]], \"id\": 1}", name, start, type, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_follow_count_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
 
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"call\", \"params\": [\"follow_api\", \"get_follow_count\", [\"%s\"]], \"id\": 1}", name );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int login_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  const char* key = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);
 
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"call\", \"params\": [\"login_api\", \"login\", [\"%s\", \"%s\"]], \"id\": 1}", name, key );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_api_by_name_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
 
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"call\", \"params\": [\"login_api\", \"get_api_by_name\", [\"%s\"]], \"id\": 1}", name );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

static int get_feed_c( lua_State* l )
{
  CURLcode ret;
  CURL *hnd = NULL;
  data_t chunk;
  easy_init( &hnd, &chunk );
  
  int limit = lua_tointeger(l, lua_gettop(l));
  lua_pop(l, 1);
  
  int entry_id = lua_tointeger(l, lua_gettop(l));
  lua_pop(l, 1);
  
  const char* name = lua_tostring(l, lua_gettop(l));
  lua_pop(l, 1);

  char jstr[512] = "";
  sprintf( jstr, "{\"jsonrpc\": \"2.0\", \"method\": \"call\", \"params\": [\"follow_api\", \"get_feed\", [\"%s\",\"%d\",\"%d\"]], \"id\": 1}", name, entry_id, limit );
  int len = strlen(jstr);
  
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, jstr);
  curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)len);
  ret = curl_easy_perform(hnd);
  
  easy_post( l, &hnd, &chunk );

  return 2;
}

/*
 * Registering functions
 */

static const struct luaL_Reg steemapi[] = {
	// Tags
	{"get_trending_tags", get_trending_tags_c},
	{"get_discussions_by_trending", get_discussions_by_trending_c},
	{"get_discussions_by_created", get_discussions_by_created_c},
	{"get_discussions_by_active", get_discussions_by_active_c},
	{"get_discussions_by_cashout", get_discussions_by_cashout_c},
	{"get_discussions_by_payout", get_discussions_by_payout_c},
	{"get_discussions_by_votes", get_discussions_by_votes_c},
	{"get_discussions_by_children", get_discussions_by_children_c},
	{"get_discussions_by_hot", get_discussions_by_hot_c},
	{"get_discussions_by_feed", get_discussions_by_feed_c},
	{"get_discussions_by_blog", get_discussions_by_blog_c},
	{"get_discussions_by_comments", get_discussions_by_comments_c},
	// Blocks and transactions
	{"get_block_header", get_block_header_c},
	{"get_block", get_block_c},
	{"get_state", get_state_c},
	// Globals
	{"get_config", get_config_c},
	{"get_dynamic_global_properties", get_dynamic_global_properties_c},
	{"get_chain_properties", get_chain_properties_c},
	{"get_feed_history", get_feed_history_c},
	{"get_current_median_history_price", get_current_median_history_price_c},
	{"get_hardfork_version", get_hardfork_version_c},
	{"get_next_scheduled_hardfork", get_next_scheduled_hardfork_c},
	{"get_reward_fund", get_reward_fund_c},
	{"get_vesting_delegations", get_vesting_delegations_c},
	// Keys
	{"get_key_references", get_key_references_c},
	// Accounts
	{"get_accounts", get_accounts_c},
	{"get_account_references", get_account_references_c},
	{"lookup_account_names", lookup_account_names_c},
	{"lookup_accounts", lookup_accounts_c},
    {"get_account_count", get_account_count_c},
	{"get_conversion_requests", get_conversion_requests_c},
	{"get_account_history", get_account_history_c},
	{"get_recovery_request", get_recovery_request_c},
	// Market
	{"get_order_book", get_order_book_c},
	{"get_open_orders", get_open_orders_c},
	{"get_liquidity_queue", get_liquidity_queue_c},
	// Authority / validation
	{"get_transaction_hex", get_transaction_hex_c},
	{"get_transaction", get_transaction_c},
	{"get_required_signatures", get_required_signatures_c},
	{"get_potential_signatures", get_potential_signatures_c},
	{"verify_authority", verify_authority_c},
	{"verify_account_authority", verify_account_authority_c},
	// Votes
	{"get_active_votes", get_active_votes_c},
	{"get_account_votes", get_account_votes_c},
	// Content
	{"get_content", get_content_c},
	{"get_content_replies", get_content_replies_c},
	{"get_discussions_by_author_before_date", get_discussions_by_author_before_date_c},
	{"get_replies_by_last_update", get_replies_by_last_update_c},
	// Witnesses
	{"get_witnesses", get_witnesses_c},
	{"get_witness_by_account", get_witness_by_account_c},
	{"get_witnesses_by_vote", get_witnesses_by_vote_c},
	{"lookup_witness_accounts", lookup_witness_accounts_c},
	{"get_witness_count", get_witness_count_c},
	{"get_active_witnesses", get_active_witnesses_c},
	{"get_miner_queue", get_miner_queue_c},
	// Login API
	{"login", login_c},
	{"get_api_by_name", get_api_by_name_c},
	{"get_feed", get_feed_c},
	// Follow API
	{"get_followers", get_followers_c},
	{"get_following", get_following_c},
	{"get_follow_count", get_follow_count_c},
	// Broadcast API

    {NULL, NULL}
};

int __declspec(dllexport)luaopen_steem(lua_State* l)
{
    luaL_newlibtable(l, steemapi);
    luaL_setfuncs(l, steemapi, 0);
    return 1;
}
} // end extern "C"
