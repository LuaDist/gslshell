

function qdho_matrix (w, k, nu, n)
   local m = cnew(n,n)
   for j=0,n-1 do
      m:set(j,j,1i*w*nu - k/2*(2*j+nu))
      if j < n-1 then m:set(j,j+1,k*math.sqrt((j+1)*(j+nu+1))) end
   end
   return m
end

s = code {f= function(t,y,f) set(f, cmul(m, y)) end, n=5}
