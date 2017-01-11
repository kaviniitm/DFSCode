# DFSCode

## Synopsis

This C++ project generates the minimum DFS Code for a given graph.

## Algorithm
• The Algorithm starts with dfs from a vertex with least label.
<br />
• While dfs traversal in the current vertex, we take the all the back edges first, sort it according to how
the edge will contribute to the Dfs code (Sorted according the dfs number of the visted node). Then
in than sorted order those edges are traversed. (Note that there is no recursive call in this section)
<br />
• After covering all the back edges from the current vertex, we take all the front edges and sort according
to its edge label, if edge labels are equal the vertex labels are considered. In this sorted order of front
edges, if there is an unique smallest edge, we take that route and call dfs recursively.
<br />
• If there is not an unique smallest edge,i.e. lets say there are n edges with same edge label and vertex
label. Out of the n options, we should decide which way to continue the traversal.
<br />
• Let the current vertex now be A and save the current status of Dfs.
<br />
• Now we decide upon a depth D ∈ 1, 2, 4, 8, ...
<br />
• Reset the current status 2 previous step from Take the next option out of the n options (If it is first
time take the first option).
<br />
• Do Dfs traversal with the chosen option until depth D (i.e. until we traverse D more edges).
<br />
• Store the Dfs traversal code obtained and if there still options left of the n options Go back 2 steps.
<br />
• Out of all n Dfs traversal if there is unique minimum then reset as current node as A and take the
option which gave the unique minimum.
<br />
• Out of all n Dfs traversal if there is a minimum but the depth is < D (i.e. the dfs traversal is not cut
by D it got ended because that branch is completely traversed) then reset the current node as A and
take that option.
<br />
• If we cant decide then increase in value of D and repeat the process until we can decide or until D is
number of edges itself (even then if a unique minimum is not found then all the options which gives
the minimum are symmetric).
<br />
• Then we can choose any one of them

## Contributors

Definition of the DFS Code is taken from the paper from the paper, <br />
gSpan:Graph-Based Substructure Pattern Mining <br />
(Xifeng Yan, Jiawei Han)<br />
http://www.cs.ucsb.edu/~xyan/papers/gSpan-short.pdf
