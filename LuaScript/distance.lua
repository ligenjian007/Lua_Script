function distance(stockx,stocky)
	return stockx.lastprice-stocky.lastprice;
end

co=coroutine.create(
	function()
	local stock1=history_data(stockname1,20130124,144500,20130124,150000)
	local stock2=history_data(stockname2,20130124,144500,20130124,150000)
	local stock3=history_data(stockname3,20130124,144500,20130124,150000)
	local stock4=history_data(stockname4,20130124,144500,20130124,150000)
	result_out:write(distance(stock1,stock1),distance(stock1,stock2),distance(stock1,stock3),distance(stock1,stock4))
	result_out:write(distance(stock2,stock1),distance(stock2,stock2),distance(stock2,stock3),distance(stock2,stock4))
	result_out:write(distance(stock3,stock1),distance(stock3,stock2),distance(stock3,stock3),distance(stock3,stock4))
	result_out:write(distance(stock4,stock1),distance(stock4,stock2),distance(stock4,stock3),distance(stock4,stock4))
	end
)

stockname1="IF302"
stockname2="IF303"
stockname3="IF306"
stockname4="IF309"
coroutine.resume(co)