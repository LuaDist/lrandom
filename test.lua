-- test random library

print(random.version)
print""

r=random.new(1234)

print("new",r:value(),r:value(),r:value())
s=r:clone()
print("more",r:value(),r:value(),r:value())
r:seed(5678)
print("seed",r:value(),r:value(),r:value())
r:seed(1234)
print("seed",r:value(),r:value(),r:value())
print("more",r:value(),r:value(),r:value())
print("clone",s:value(),s:value(),s:value())

r:seed(os.time())
N=100000

S={0,0,0,0,0,0,0,0,0,0,0}
for i=1,N do
 local i=r:valuei(8)
 S[i]=S[i]+1
end
for i=1,9 do
 S[i]=math.floor(100*S[i]/N+0.5)
end
print("1..8",S[1],S[2],S[3],S[4],S[5],S[6],S[7],S[8])

S={0,0,0,0,0,0,0,0,0,0,0}
for i=1,N do
 local i=r:valuei(2,4)
 S[i]=S[i]+1
end
for i=1,9 do
 S[i]=math.floor(100*S[i]/N+0.5)
end
print("2..4",S[1],S[2],S[3],S[4],S[5],S[6],S[7],S[8])

print""
print(random.version)
