co=coroutine.create(
	function()
	print(connect())
	print(get_lastprice())
	end)
	
coroutine.resume(co)
sleep(100000)