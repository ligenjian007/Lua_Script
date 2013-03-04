co1=coroutine.create(
function()
print("hello world")
bool,history=history_data("IF1302",20130124,134000,20130124,143000)
print(bool,history.openprice,history.askprice1)
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
