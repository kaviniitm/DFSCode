#include<bits/stdc++.h>
using namespace std;

const int inf = 10000000;

struct Edge
{
  int src;
  int dest;
  string lbl;
  Edge(int src, int dest, string lbl)
  {
    this->src = src;
    this->dest = dest;
    this->lbl = lbl;
  }
  Edge(int src, int dest)
  {
    this->src = src;
    this->dest = dest;
  }
};

struct DfsEdge
{
  int vertex1;
  int vertex2;
  string label1;
  string edge_label;
  string label2;

  DfsEdge(int vertex1, int vertex2, string label1, string edge_label, string label2)
  {
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
    this->label1 = label1;
    this->edge_label = edge_label;
    this->label2 = label2;
  }
  void print()
  {
    //cout<<"("<<vertex1<<", "<<vertex2<<", "<<label1<<", "<<edge_label<<", "<<label2<<")";
    cout<<"<"<<vertex1<<","<<vertex2<<","<<label1<<","<<edge_label<<","<<label2<<">";
  }

  bool operator<(DfsEdge e)
  {
    if(this->vertex2<this->vertex1 && e.vertex2>e.vertex1)
      return true;
    if(this->vertex2<this->vertex1 && e.vertex2<e.vertex1 && this->vertex2<e.vertex2)
      return true;
    if(this->vertex2<this->vertex1 && e.vertex2<e.vertex1 && this->vertex2==e.vertex2 && this->edge_label<e.edge_label)
      return true;
    if(this->vertex2>this->vertex1 && e.vertex2>e.vertex1 && e.vertex1<this->vertex1)
      return true;
    if(this->vertex2>this->vertex1 && e.vertex2>e.vertex1 && e.vertex1==this->vertex1 && this->label1<e.label1)
      return true;
    if(this->vertex2>this->vertex1 && e.vertex2>e.vertex1 && e.vertex1==this->vertex1 && this->label1==e.label1 && this->edge_label<e.edge_label)
      return true;
    if(this->vertex2>this->vertex1 && e.vertex2>e.vertex1 && e.vertex1==this->vertex1 && this->label1==e.label1 && this->edge_label==e.edge_label && this->label2<e.label2)
      return true;
    return false;
/*
    if(this->vertex1 != e.vertex1)
      return (this->vertex1 < e.vertex1);
    if(this->vertex2 != e.vertex2)
      return (this->vertex2 < e.vertex2);
    if(this->label1 != e.label1)
      return (this->label1 < e.label1);
    if(this->edge_label != e.edge_label)
      return (this->edge_label < e.edge_label);
    if(this->label2 != e.label2)
      return (this->label2 < e.label2);
    return false;
*/
  }
  bool operator==(DfsEdge e)
  {
    if(this->vertex1 != e.vertex1)
      return false;
    if(this->vertex2 != e.vertex2)
      return false;
    if(this->label1 != e.label1)
      return false;
    if(this->edge_label != e.edge_label)
      return false;
    if(this->label2 != e.label2)
      return false;
    return true;
  }
};

vector<Edge> universal_edges;
vector<string> universal_labels;
int universal_u;
vector<int> universal_dfs_number;

bool backEdgeComparator(int i, int j)
{
  Edge e1 = universal_edges[i];
  Edge e2 = universal_edges[j];
  int v1 = (e1.src!=universal_u)?e1.src:e1.dest;
  int v2 = (e2.src!=universal_u)?e2.src:e2.dest;
  return (universal_dfs_number[v1]<universal_dfs_number[v2]);
}
bool frontEdgeComparator(int i, int j)
{
  Edge e1 = universal_edges[i];
  Edge e2 = universal_edges[j];
  if(e1.lbl != e2.lbl)
    return (e1.lbl < e2.lbl);
  int v1 = (e1.src!=universal_u)?e1.src:e1.dest;
  int v2 = (e2.src!=universal_u)?e2.src:e2.dest;
  return (universal_labels[v1] < universal_labels[v2]);
}

void print(vector<DfsEdge> code)
{
  int i;
  for(i=0;i<code.size();++i)
  {
    code[i].print();
    cout<<endl;
  }
}

struct Graph
{
  int n, m;
  vector<string> labels;
  vector<vector< int > > adj_list;
  vector<bool> vertex_vis;
  vector<bool> edge_vis;
  vector<int> dfs_number;
  int disc;
  vector<Edge> edges;
  vector<DfsEdge> min_code;
  vector< pair<int,int> > min_vertex_code;
  bool min_code_set;
  vector<DfsEdge> code;
  vector< pair<int,int> > vertex_code;
  vector<int> parent;

  Graph(int _n)
  {
    this->n = _n;
    labels.clear();
    adj_list.resize(n);
    min_code_set = false;
  }
  bool isLesser(vector<DfsEdge> a, vector<DfsEdge> b)
  {
    int i;
    for(i=0;i<min(a.size(),b.size());++i)
      if(a[i]<b[i])
        return true;
      else if(!(a[i]==b[i]))
        return false;
    return false;
  }
  bool isGreater(vector<DfsEdge> a, vector<DfsEdge> b)
  {
    int i;
    for(i=0;i<min(a.size(),b.size());++i)
    {
      if(a[i]<b[i])
        return false;
        if(b[i]<a[i])
        return true;
    }
    return false;
  }

  void sappa_dfs(int u)
  {
    vertex_vis[u] = true;
    int i;
    for(i=0;i<adj_list[u].size();++i)
    {
      int v = (edges[adj_list[u][i]].src!=u)?edges[adj_list[u][i]].src:edges[adj_list[u][i]].dest;
      if(!vertex_vis[v])
        sappa_dfs(v);
    }
  }
  bool checkForConnectivity()
  {
    int i;
    for(i=0;i<n;++i)
      vertex_vis.push_back(false);
    sappa_dfs(0);
    for(i=0;i<n;++i)
      if(!vertex_vis[i])
        return 0;
    return 1;
  }

  void checkForMin(vector<DfsEdge> code)
  {
    if(!min_code_set || isLesser(code, min_code))
    {
      min_code = code;
      min_vertex_code = vertex_code;
      min_code_set = true;
    }
  }

  bool no_use_flag;
  void print_stack()
  {
    int i;
    for(i=0;i<vertex_code.size();++i)
      cout<<"("<<vertex_code[i].first<<","<<vertex_code[i].second<<")";
  }

  int dfs(int u, int d)
  {
//cout<<"stack size: "<<vertex_code.size()<<endl;
//print_stack();
//cout<<endl;
    if(code.size()==m)
    {
      checkForMin(code);
      return 1;
    }
    if(d==0)
      return 0;
//    if(no_use_flag)
//      return;

    vector<int> nei = adj_list[u];
    vector<int> back, front;
    for(int i=0;i<nei.size();++i) // Populate back and front
    {
      int v = (edges[nei[i]].src!=u)?edges[nei[i]].src:edges[nei[i]].dest;
      if(v==parent[u])
        continue;
      if(edge_vis[nei[i]])
        continue;
      if(vertex_vis[v]==true)
        back.push_back(nei[i]);
      else
        front.push_back(nei[i]);
    }

    int i;
    universal_u = u;
    universal_dfs_number = dfs_number;
    sort(back.begin(), back.end(), backEdgeComparator);
//cout<<"vertex: "<<u<<" backedge sorted: "<<endl;
//for(i=0;i<back.size();++i)cout<<back[i]<<" ";cout<<endl;

    sort(front.begin(), front.end(), frontEdgeComparator);
//for(i=0;i<front.size();++i)cout<<front[i]<<" ";cout<<endl;
    vector<int> start, end;
    i=0;
    while(i<front.size()) // Populate start and end
    {
      start.push_back(i);
      while(i<front.size())
      {
        if(i==front.size()-1)
        {
          end.push_back(i);
          i++;
          break;
        }
        Edge e1 = edges[front[i]];
        Edge e2 = edges[front[i+1]];
        int v1 = (e1.src!=u)?e1.src:e1.dest;
        int v2 = (e2.src!=u)?e2.src:e2.dest;
        if(e1.lbl==e2.lbl && labels[v1]==labels[v2])
          i++;
        else
        {
          end.push_back(i);
          i++;
          break;
        }
      }
    }
//    cout<<"vertex: "<<u<<endl;
//    cout<<"start: ";for(i=0;i<start.size();++i)cout<<start[i]<<" ";cout<<endl;
//    cout<<"end: ";for(i=0;i<end.size();++i)cout<<end[i]<<" ";cout<<endl;
    vector<vector<int>::iterator> start_it, end_it;
    vector<int>::iterator it = front.begin();
    i = 0;
    while(it!=front.end())  //Populate start_it and end_it
    {
      start_it.push_back(it);
      int j;
      for(j=0;j<end[i]-start[i];++j)
        it++;
      end_it.push_back(it);
      it++;
      i++;
    }

    for(i=0;i<back.size();++i)//Populate code with back edges
    {
      if(edge_vis[back[i]])
        continue;
      edge_vis[back[i]] = true;
      int v = (edges[back[i]].src!=u)?edges[back[i]].src:edges[back[i]].dest;
      DfsEdge e(dfs_number[u], dfs_number[v], labels[u], edges[back[i]].lbl, labels[v]);
      code.push_back(e);
      d--;
      vertex_code.push_back(make_pair(u,v));
      if(code.size()==m)
        checkForMin(code);
      if(d==0)
        return 0;
      if(min_code_set && isGreater(code, min_code))
      {
//cout<<"$no use anymore"<<endl;
        no_use_flag = true;
        return 0;
      }

    }
    vector<bool> vertex_vis_status = vertex_vis;
    vector<bool> edge_vis_status = edge_vis;
    vector<DfsEdge> code_status = code;
    vector< pair<int,int> > vertex_code_status = vertex_code;
    vector<int> dfs_number_status = dfs_number;
    vector<int> parent_status = parent;
    int disc_status = disc;

    for(i=0;i<start.size();++i)
    {
      bool dec_i = false;
      if(end[i]-start[i]!=0)
      {
//cout<<"vertex: "<<u<<" end[i]-start[i]: "<<end[i]-start[i]<<endl;
//cout<<"decision maker"<<endl;
        vertex_vis_status = vertex_vis;
        edge_vis_status = edge_vis;
        code_status = code;
        vertex_code_status = vertex_code;
        dfs_number_status = dfs_number;
        parent_status = parent;
        disc_status = disc;

        int previous_code_size = code.size();
        for(int D=1;D<=d;D*=2)
        {
//cout<<"vertex: "<<u<<" starting with D: "<<D<<endl;
          int perm_num = 0;
          vector< vector<DfsEdge> > codes;
          vector<int>::iterator it;
          vector<int>::iterator end_plus = end_it[i]; end_plus++;
          vector<DfsEdge> extended_code;
          vector<int> rets;
          int size = 0;
          for(it=start_it[i];it!=end_plus;++it)
          {
            codes.push_back(code);
            rets.push_back(0);
          }
          int num = 0;
          for(it=start_it[i];it!=end_plus;++it,++num)
          {
//cout<<"codes.size(): "<<codes.size()<<" *it: "<<*it<<endl;
          int D_left = D;
        int d_left = d;
            vertex_vis = vertex_vis_status;
            edge_vis = edge_vis_status;
            code = code_status;
            vertex_code = vertex_code_status;
            dfs_number = dfs_number_status;
            parent = parent_status;
            disc = disc_status;

            D_left = D;
  //          for(it = start_it[i]; it!=end_plus; ++it)
  //          {
              if(edge_vis[*it])
              {
//cout<<"^&*"<<endl;
                continue;
              }
              edge_vis[*it] = true;
              int v = (edges[*it].src!=u)?edges[*it].src:edges[*it].dest;
              if(!vertex_vis[v])
              {
                vertex_vis[v] = true;
                dfs_number[v] = disc++;
                DfsEdge e(dfs_number[u], dfs_number[v], labels[u], edges[*it].lbl, labels[v]);
                code.push_back(e);
                D_left--;
                d_left--;
                vertex_code.push_back(make_pair(u,v));
                parent[v] = u;
                int code_size = code.size();
                int ret = dfs(v,min(D_left, d_left));
                rets[num] = ret;
                int extended_code_size = code.size() - code_size;
                D_left -= extended_code_size;
                d_left -= extended_code_size;
              }
            //codes.push_back(code);
            codes[num] = code;
//cout<<"pushing into codes"<<endl;
/*              if(D_left==0)
                break;
              if(code.size()==m)
                break;
*/
//            }
            }
//          while(next_permutation(start_it[i], end_plus));
//cout<<"vertex: "<<u<<" done with D: "<<D<<endl;
          int j;
//for(j=0;j<codes.size();++j){print(codes[j]);cout<<endl;}
          if(codes.size()==0)
            break;
          vector<DfsEdge> local_min_code = codes[0];
          int perm = 0;
          bool solo_min = true;
//cout<<"codes.size(): "<<codes.size()<<endl;
          for(j=1;j<codes.size();++j)
          {
//cout<<"hello j: "<<j<<" code.size(): "<<codes.size()<<endl;
            if(isLesser(codes[j], local_min_code))
            {
              local_min_code = codes[j];
              perm = j;
              solo_min = true;
            }
            else if(!isGreater(codes[j], local_min_code))
              solo_min = false;
          }
              bool break_flag=false;
          for(j=0;j<codes.size();++j)
          {
//cout<<"!@#"<<endl;
          if(!isLesser(codes[j], local_min_code) && !isGreater(codes[j], local_min_code))
            {
//cout<<"^&*"<<endl;
//cout<<"*()"<<endl;
              if(rets[j]==1)
              {
                break_flag = true;
                perm = j;
              }
            }
          }

//cout<<"solo_min: "<<solo_min<<" codes.size():"<<codes.size()<<endl;
//              if(previous_code_size==code.size())
//                break_flag = true;
              previous_code_size = code.size();

              vertex_vis = vertex_vis_status;
              edge_vis = edge_vis_status;
              code = code_status;
              vertex_code = vertex_code_status;
              dfs_number = dfs_number_status;
              parent = parent_status;
              disc = disc_status;

          if(solo_min || D*2>m || break_flag)
          {
            vector<int>::iterator it = start_it[i];
            int temp_perm = perm;
            while(temp_perm--)
              it++;
//cout<<"vertex : "<<u<<" found solo min when D: "<<D<<" perm: "<<perm<<" *start_it[i]: "<<*start_it[i]<<" *it: "<<*it<<endl;
            int temp = *start_it[i];
            *start_it[i] = *it;
            *it = temp;
            dec_i = true;
            break;
/*          int perm_num = 0;
            do
            {
              if(perm_num==perm)
                break;
              perm_num++;
            }while(next_permutation(start_it[i], end_plus));
            break;
*/
          }
          if(break_flag)
          {
//cout<<"no use going full D"<<endl;
            break;
          }
        }
      }
      vector<int>::iterator it;
      vector<int>::iterator end = end_it[i];end++;
//cout<<"!@#"<<endl;
      for(it=start_it[i];it==start_it[i];++it)
      {
        if(edge_vis[*it])
          continue;
        edge_vis[*it] = true;
        int v = (edges[*it].src!=u)?edges[*it].src:edges[*it].dest;
//cout<<"from vertex "<<u<<" to "<<"vertex "<<v<<endl;
        if(!vertex_vis[v])
        {
          vertex_vis[v] = true;
          dfs_number[v] = disc++;
          DfsEdge e(dfs_number[u], dfs_number[v], labels[u], edges[*it].lbl, labels[v]);
          code.push_back(e);
          d--;
          vertex_code.push_back(make_pair(u,v));
          parent[v] = u;
          int code_size = code.size();
          if(code.size()==m)
            checkForMin(code);
          if(d==0)
            return 0;
          if(min_code_set && isGreater(code, min_code))
          {
//cout<<"vertex u:"<<u<<" @no use anymore"<<endl;
            no_use_flag = true;
            return 0;
          }
//cout<<"from vertex: "<<u<<" going to vertex: "<<v<<endl;
          dfs(v, d);
          int extended_code_size = code.size() - code_size;
          d -= extended_code_size;
          if(code.size()==m)
            checkForMin(code);
          if(d==0)
            return 0;
        }
        else
        {
          DfsEdge e(dfs_number[u], dfs_number[v], labels[u], edges[*it].lbl, labels[v]);
          code.push_back(e);
          vertex_code.push_back(make_pair(u,v));
          d--;
          if(code.size()==m)
            checkForMin(code);
          if(d==0)
            return 0;
        }
      }
      if(dec_i)
      {
        start[i]++;
        start_it[i]++;
        i--;
      }
    }
    return 1;
  }

  void getMinDFSCode()
  {
    int i;
    min_code_set = false;
    vector<string> sortted_labels = labels;
    sort(sortted_labels.begin(), sortted_labels.end());
    string least_label = sortted_labels[0];
    for(int src=0;src<n;++src)
    {
      if(labels[src]!=least_label)
        continue;
      no_use_flag = false;
//cout<<"src: "<<src<<endl;
//      if(src==36)print(min_code);cout<<endl;
      vertex_vis.resize(n);
      edge_vis.resize(m);
      parent.resize(n);
      for(i=0;i<n;++i)
      {
        vertex_vis[i] = false;
        parent[i] = -1;
      }
      for(i=0;i<m;++i)
        edge_vis[i] = false;
      dfs_number.resize(n);
      code.clear();
      vertex_code.clear();
      disc = 0;
      vertex_vis[src] = true;
      //code.push_back(src);
      dfs_number[src] = disc++;
      dfs(src, m);
    }
    for(i=0;i<min_code.size();++i)
    {
      min_code[i].print();
//      cout<<" "<<min_vertex_code[i].first<<" "<<min_vertex_code[i].second;
//      cout<<endl;
    }
    cout<<endl;
  }
};

int main()
{
  int start = clock();
  int graph_count = 1;
  string graph_id;
  while((cin>>graph_id))
  {
    int n;
    cin>>n;
    Graph g(n);
    int i;
    for(i=0;i<g.n;++i)
    {
      string lbl;
      cin>>lbl;
      g.labels.push_back(lbl);
    }
    universal_labels = g.labels;
    cin>>g.m;
    for(i=0;i<g.m;++i)
    {
      int src,dest;
      string lbl;
      cin>>src>>dest>>lbl;
      Edge e(src,dest,lbl);
      g.edges.push_back(e);
      g.adj_list[src].push_back(g.edges.size()-1);
      g.adj_list[dest].push_back(g.edges.size()-1);
    }
    universal_edges = g.edges;
    int j;
    for(i=0;i<g.n;++i)
    {
      sort(g.adj_list[i].begin(), g.adj_list[i].end());
    }
//cout<<g.checkForConnectivity()<<endl;
//    cout<<"graph number: "<<graph_count++<<" graph id: "<<graph_id<<" n: "<<g.n<<" m: "<<g.m<<endl;
    g.getMinDFSCode();
  }
//  cout<<"Time: "<<(double)(clock() - start)/1000000<<endl;
  DfsEdge e1(1,2,"C","1","Fe"), e2(1,2,"C","1","C");

//  cout<<(e2<e1)<<endl;
}
