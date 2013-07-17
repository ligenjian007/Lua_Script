co=coroutine.create(
function()
buyprice=get_askprice("IF1307")
sellprice=get_bidprice("IF1308")
if buyprice<sellprice then
	trade("IF1307","0",buyprice+1, "0")
	buyprice=get_buyprice(0)
	trade("IF1308","1",sellprice-1, "0")
	sellprice=get_sellprice(0)

	while (sleep(1000)) do
		if (buyprice~=0 and sellprice~=0) then
			buyprice_now=get_askprice("IF1308")
			sellprice_now=get_bidprice("IF1307")
			if buyprice_now==sellprice_now or (sellprice_now - buyprice_now + sellprice - buyprice >=1) or (sellprice_now - buyprice_now + sellprice - buyprice <=-2) then
				trade("IF1307", "1",sellprice_now-1,"3")
				trade("IF1308", "0",buyprice_now+1,"3")
				break
			else 
				buyprice=get_buyprice(0)
				sellprice=get_sellprice(0)
			end
		else
			buyprice=get_buyprice(0)
			sellprice=get_sellprice(0)
		end
	end
else 
	buyprice=get_askprice("IF1308")
	sellprice=get_bidprice("IF1307")
	if buyprice<sellprice then
		trade("IF1308","0",buyprice+1, "0")
		buyprice=get_buyprice(0)
		trade("IF1307","1",sellprice-1, "0")
		sellprice=get_sellprice(0)
		while (1==1) do
			if (buyprice~=0 and sellprice~=0) then
				buyprice_now=get_askprice("IF1307")
				sellprice_now=get_bidprice("IF1308")
				if (buyprice_now==sellprice_now or (sellprice_now - buyprice_now + sellprice - buyprice) >=1 or (sellprice_now - buyprice_now + sellprice - buyprice) <=-2) then
					trade("IF1308", "1",sellprice_now-1,"3")
					trade("IF1307", "0",buyprice_now+1,"3")
					break
				else 
					buyprice=get_buyprice(0)
					sellprice=get_sellprice(0)
				end
			else
				buyprice=get_buyprice(0)
				sellprice=get_sellprice(0)
			end
		end
	end
end
end
)


coroutine.resume(co)
print("finished execute")
print(coroutine.status(co))
sleep(4000)