buyprice=get_askprice("IF1307")
sellprice=get_bidprice("IF1308")
if buyprice<sellprice then
	trade("IF1307",'0',buyprice+1, '0')
	buyprice=0
	trade("IF1308",'1',sellprice-1, '0')
	sellprice=0
	
	while true do
		if buyprice!=0 and sellprice!=0 then
			buyprice_now=get_askprice("IF1308")
			sellprice_now=get_bidprice("IF1307")
			if buyprice_now==sellprice_now or (sellprice_now - buyprice_now + sellprice - buyprice >=1) or (sellprice_now - buyprice_now + sellprice - buyprice <=-2) then
				trade("IF307", '1',sellprice_now-1,'3')
				sellprice=0
				trade("IF308", '0',buyprice_now+1,'3')
				buyprice=0
				break
			end
		end
	end
else 
	buyprice=get_askprice("IF1307")
	sellprice=get_bidprice("IF1308")
	if buyprice<sellprice then
		trade("IF1307",'0',buyprice+1, '0')
		buyprice=0
		trade("IF1308",'1',sellprice-1, '0')
		sellprice=0
	
		while true do
			if buyprice!=0 and sellprice!=0 then
				buyprice_now=get_askprice("IF1308")
				sellprice_now=get_bidprice("IF1307")
				if buyprice_now==sellprice_now or (sellprice_now - buyprice_now + sellprice - buyprice >=1) or (sellprice_now - buyprice_now + sellprice - buyprice <=-2) then
					trade("IF307", '1',sellprice_now-1,'3')
					sellprice=0
					trade("IF308", '0',buyprice_now+1,'3')
					buyprice=0
					break
				end
			end
		end
	end
end