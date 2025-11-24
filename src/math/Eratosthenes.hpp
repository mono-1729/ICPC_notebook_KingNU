int max_num = 1000005;
vector<int> erat(max_num);
void init_e() {
   for(ll i = 2; i*i <= max_num; i++) {
      if(erat[i] == 0) {
         for(ll j = i * i; j <= max_num - 1; j += i) {
            if(erat[j] == 0) erat[j] = i;
         }
      }
   }
}