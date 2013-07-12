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
bool,stock1[0]=history_data(stockname1,20130124,144500,20130124,150000)
bool,stock1[1]=history_data(stockname1,20130124,143000,20130124,144500)
bool,stock1[2]=history_data(stockname1,20130124,141500,20130124,143000)
print("finish read 1");
bool,stock2[0]=history_data(stockname2,20130124,144500,20130124,150000)
bool,stock2[1]=history_data(stockname2,20130124,143000,20130124,144500)
bool,stock2[2]=history_data(stockname2,20130124,141500,20130124,143000)
print("finish read 2")
bool,stock3[0]=history_data(stockname3,20130124,144500,20130124,150000)
bool,stock3[1]=history_data(stockname3,20130124,143000,20130124,144500)
bool,stock3[2]=history_data(stockname3,20130124,141500,20130124,143000)
print("finish read 3")
bool,stock4[0]=history_data(stockname4,20130124,144500,20130124,150000)
bool,stock4[1]=history_data(stockname4,20130124,143000,20130124,144500)
bool,stock4[2]=history_data(stockname4,20130124,141500,20130124,143000)
print("finish read 4")
--print(correlation(stock1,stock1),correlation(stock1,stock2),correlation(stock1,stock3),correlation(stock1,stock4))
--print(correlation(stock2,stock1),correlation(stock2,stock2),correlation(stock2,stock3),correlation(stock2,stock4))
--print(correlation(stock3,stock1),correlation(stock3,stock2),correlation(stock3,stock3),correlation(stock3,stock4))
--print(correlation(stock4,stock1),correlation(stock4,stock2),correlation(stock4,stock3),correlation(stock4,stock4))
result_out:write(correlation(stock1,stock1),correlation(stock1,stock2),correlation(stock1,stock3),correlation(stock1,stock4))
result_out:write(correlation(stock2,stock1),correlation(stock2,stock2),correlation(stock2,stock3),correlation(stock2,stock4))
result_out:write(correlation(stock3,stock1),correlation(stock3,stock2),correlation(stock3,stock3),correlation(stock3,stock4))
result_out:write(correlation(stock4,stock1),correlation(stock4,stock2),correlation(stock4,stock3),correlation(stock4,stock4))
print("finish write")
end

stockname1="IF1303"
stockname2="IF1306"
stockname3="IF1309"
stockname4="IF1302"

co=coroutine.create(stockcorrelation)
coroutine.resume(co)
while coroutine.status(co)=="suspended" do
	sleep(10000)
end