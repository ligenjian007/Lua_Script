co1=coroutine.create(
function()
print("hello world")
bool,history=history_data()
print(bool,history.open_price,history.askprice1)
end)

co2=coroutine.create(
function()
print("in co2")
bool,en=entrust()
print(bool,en.local_id,en.entrust_no)
end)

print(connect())
coroutine.resume(co1)
coroutine.resume(co2)
sleep(300000)
