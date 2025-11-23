int max_num = 1000005;
vector<int> erat(max_num);
void init_e() {
   rep(i, 2, sqrt(max_num - 1)) {
      if(erat[i] == 0) {
         for(int j = i * i; j <= max_num - 1; j += i) {
            if(erat[j] == 0) erat[j] = i;
         }
      }
   }
}