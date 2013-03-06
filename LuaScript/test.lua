function correlation(stocka,stockb)
--	print("in function")
--	print(stocka[0].lastprice)
--	print(stocka[1].lastprice)
--	print(stocka[2].lastprice)
	avga=(stocka[0].lastprice+stocka[1].lastprice+stocka[2].lastprice)/3
	avgb=(stockb[0].lastprice+stockb[1].lastprice+stockb[2].lastprice)/3
--	print("avg",avga,avgb)
	nume=0
	for i=0,2 do
		nume=nume+(stocka[i].lastprice-avga)*(stockb[i].lastprice-avgb)
	end
--	print("nume",nume)
	denoa=0
	for i=0,2 do
		denoa=denoa+(stocka[i].lastprice-avga)*(stocka[i].lastprice-avga)
	end
	denoa=math.sqrt(denoa)
--	print("denoa",denoa)
	denob=0
	for i=0,2 do
		denob=denob+(stockb[i].lastprice-avgb)*(stockb[i].lastprice-avgb)
	end
	denob=math.sqrt(denob)
--	print("denob",denob)
	return nume/(denoa*denob)
end

function stockcorrelation()
stock1={}
stock2={}
stock3={}
stock4={}
print(connect())
end

		

co=coroutine.create(stockcorrelation)
coroutine.resume(co)
--while coroutine.status(co)=="suspended" do
	sleep(10000)
--end