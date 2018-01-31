s = require("steem")

--[[
local jstr, n = s.get_account_count()
print (jstr .. n)

jstr, n = s.lookup_accounts("alan",100)
print (jstr .. n)

jstr, n = s.get_dynamic_global_properties()
print (jstr .. n)

jstr, n = s.get_trending_tags("cn", 10)
print (jstr .. n)

jstr, n = s.get_discussions_by_trending("cn", "alanzheng", "curl-steem-api-json-object-or-how-to-call-steem-api-by-curl", 1)
print (jstr .. n)

jstr, n = s.get_discussions_by_created("cn", "alanzheng", "curl-steem-api-json-object-or-how-to-call-steem-api-by-curl", 1)
print (jstr .. n)

jstr, n = s.get_discussions_by_active("cn", "alanzheng", "curl-steem-api-json-object-or-how-to-call-steem-api-by-curl", 1)
print (jstr .. n)

jstr, n = s.get_discussions_by_cashout("cn", "alanzheng", "curl-steem-api-json-object-or-how-to-call-steem-api-by-curl", 1)
print (jstr .. n)

jstr, n = s.get_discussions_by_payout("cn", "alanzheng", "curl-steem-api-json-object-or-how-to-call-steem-api-by-curl", 1)
print (jstr .. n)

jstr, n = s.get_discussions_by_votes("cn", "alanzheng", "curl-steem-api-json-object-or-how-to-call-steem-api-by-curl", 1)
print (jstr .. n)

jstr, n = s.get_discussions_by_children("cn", "alanzheng", "curl-steem-api-json-object-or-how-to-call-steem-api-by-curl", 1)
print (jstr .. n)

jstr, n = s.get_discussions_by_hot("cn", "alanzheng", "curl-steem-api-json-object-or-how-to-call-steem-api-by-curl", 1)
print (jstr .. n)

jstr, n = s.get_discussions_by_feed("cn", "alanzheng", "curl-steem-api-json-object-or-how-to-call-steem-api-by-curl", 1)
print (jstr .. n)

jstr, n = s.get_discussions_by_blog("alanzheng", "alanzheng", "curl-steem-api-json-object-or-how-to-call-steem-api-by-curl", 1)
print (jstr .. n)

jstr, n = s.get_discussions_by_comments("cn", "alanzheng", "curl-steem-api-json-object-or-how-to-call-steem-api-by-curl", 1)
print (jstr .. n)

jstr, n = s.get_block_header(3394332)
print (jstr .. n)

jstr, n = s.get_block(3394332)
print (jstr .. n)

jstr, n = s.get_state("/@alanzheng")
print (jstr .. n)

jstr, n = s.get_config()
print (jstr .. n)

jstr, n = s.get_feed_history()
print (jstr .. n)

jstr, n = s.get_current_median_history_price()
print (jstr .. n)

jstr, n = s.get_hardfork_version()
print (jstr .. n)

jstr, n = s.get_next_scheduled_hardfork()
print (jstr .. n)

jstr, n = s.get_reward_fund("post")
print (jstr .. n)

jstr, n = s.get_vesting_delegations("alanzheng","alanzheng",10)
print (jstr .. n)

jstr, n = s.get_key_references("your key")
print (jstr .. n)

jstr, n = s.get_accounts("alanzheng")
print (jstr .. n)

jstr, n = s.get_account_references(385242)
print (jstr .. n)

jstr, n = s.lookup_account_names("alanzheng")
print (jstr .. n)

jstr, n = s.get_conversion_requests("alanzheng")
print (jstr .. n)

jstr, n = s.get_account_history("alanzheng",1,1)
print (jstr .. n)

jstr, n = s.get_recovery_request("alanzheng")
print (jstr .. n)

jstr, n = s.get_order_book(2)
print (jstr .. n)

jstr, n = s.get_open_orders("alanzheng")
print (jstr .. n)

jstr, n = s.get_liquidity_queue("alanzheng",2)
print (jstr .. n)

jstr, n = s.get_transaction_hex(23)
print (jstr .. n)

jstr, n = s.get_transaction(23)
print (jstr .. n)

jstr, n = s.get_required_signatures(23, "")
print (jstr .. n)

jstr, n = s.get_potential_signatures(23)
print (jstr .. n)

jstr, n = s.verify_authority(23)
print (jstr .. n)

jstr, n = s.verify_account_authority("alanzheng", "")
print (jstr .. n)

jstr, n = s.get_account_votes("alanzheng")
print (jstr .. n)

jstr, n = s.get_active_votes("alanzheng", "gimp-or-gimp-tutorial-summarize")
print (jstr .. n)

jstr, n = s.get_content("alanzheng", "gimp-or-gimp-tutorial-summarize")
print (jstr .. n)

jstr, n = s.get_content_replies("alanzheng", "gimp-or-gimp-tutorial-summarize")
print (jstr .. n)

jstr, n = s.get_discussions_by_author_before_date("alanzheng", "gimp-or-gimp-tutorial-summarize", "2018-01-17T03:01:48", 1)
print (jstr .. n)

jstr, n = s.get_replies_by_last_update("alanzheng", "gimp-or-gimp-tutorial-summarize", 10)
print (jstr .. n)

jstr, n = s.get_witnesses(12336)
print (jstr .. n)

jstr, n = s.get_witness_by_account("timcliff")
print (jstr .. n)

jstr, n = s.get_witnesses_by_vote("timcliff", 10)
print (jstr .. n)

jstr, n = s.lookup_witness_accounts("timcliff", 10)
print (jstr .. n)

jstr, n = s.get_witness_count()
print (jstr .. n)

jstr, n = s.get_active_witnesses()
print (jstr .. n)

jstr, n = s.get_miner_queue()
print (jstr .. n)

jstr, n = s.get_followers("alanzheng", "*", "blog", 1000)
print (jstr .. n)

jstr, n = s.get_following("alanzheng", "*", "blog", 100)
print (jstr .. n)

jstr, n = s.get_follow_count("alanzheng")
print (jstr .. n)

jstr, n = s.login("xiaodong", "your key")
print (jstr .. n)

jstr, n = s.get_api_by_name("follow_api")
print (jstr .. n)

jstr, n = s.get_feed("alanzheng",0,1)
print (jstr .. n)
]]
local jstr, n = s.get_account_count()
print (jstr .. n)


































































