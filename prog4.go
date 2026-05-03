package main

import (
	"fmt"
)

type VoteRes struct {
	borda     string
	condorcet string
}

func calculateVoting(votes [][]string) VoteRes {
	if len(votes) == 0 || len(votes[0]) == 0 {
		return VoteRes{}
	}

	numCandidates := len(votes[0])
	bordaScores := make(map[string]int)
	var candidates []string

	for _, ballot := range votes {
		pts := numCandidates - 1
		for _, cand := range ballot {
			if _, exists := bordaScores[cand]; !exists {
				candidates = append(candidates, cand)
			}
			bordaScores[cand] += pts
			pts--
		}
	}

	maxBorda := -1
	res := VoteRes{condorcet: "None"}
	for cand, score := range bordaScores {
		if score > maxBorda {
			maxBorda = score
			res.borda = cand
		}
	}

	for _, candA := range candidates {
		winsAll := true
		for _, candB := range candidates {
			if candA == candB {
				continue
			}
			winsA, winsB := 0, 0
			for _, ballot := range votes {
				posA, posB := -1, -1
				for pos, c := range ballot {
					if c == candA {
						posA = pos
					}
					if c == candB {
						posB = pos
					}
				}
				if posA < posB {
					winsA++
				} else {
					winsB++
				}
			}
			if winsA <= winsB {
				winsAll = false
				break
			}
		}
		if winsAll {
			res.condorcet = candA
			break
		}
	}
	return res
}

func main() {
	var n, m int
	_, err := fmt.Scan(&n, &m)
	if err == nil {
		votes := make([][]string, n)
		for i := 0; i < n; i++ {
			votes[i] = make([]string, m)
			for j := 0; j < m; j++ {
				fmt.Scan(&votes[i][j])
			}
		}
		r := calculateVoting(votes)
		fmt.Println(r.borda)
		fmt.Println(r.condorcet)
	}
}
