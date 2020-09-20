#!/bin/bash

# ofxAddon dependency checker for OpenFrameworks projects.
# Works together with an addons.txt config file.

# - - - -
# MIT License
#
# Copyright (c) 03-2020 Daan de Lange - https://daandelange.com/
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# - - - - - - -


# SCRIPT NOTES
# Various lines are left commented, lots of alternative ways or debug helpers.
# Keep them until we've tested this on multiple platforms and setups.
# There's also a lot of comments on bash code, to make it more understandable for me and for other C++ programers.

#set -ex # <-- useful for debugging, shows the lines being executes during execution

# Terminal color definitions
style_red=$(tput setaf 1)
style_green=$(tput setaf 2)
style_yellow=$(tput setaf 3)
style_reset=$(tput sgr 0)

# Set directory information
curDir=`pwd`
cd "$curDir"
cd ../../../addons
addonsDir=`pwd`

# Say hello
echo ""
echo "Hello, this script will scan your addons folder and check if all the necessary addons are correctly installed."
echo "If some fields are marked red, they might need manual attention."
echo "This script is in beta phase. Only tested on osx."
echo ""
echo "Working from directory : $curDir/addons.txt"
echo "Detected addons directory : $addonsDir"
echo " "

# Table header
printf "%-20s | %-40s | %-16s | %-16s | %-16s | %-16s \n" "- - - - - - - - - - " "- - - - - - - - - - - - - - - - - - - - " "- - - - - - - - " "- - - - - - - - " "- - - - - - - - " "- - - - - - - - - - - - -"
#printf "%-30s | %-50s | %-16s | %-16s | %-16s | %-16s | %-16s \n" "Addon" "Required Repo" "Needed Branch" "Exists" "Remote URL" "Local Branch" "Local Changes"
printf "%-20s | %-40s | %-16s | %-16s | %-16s | %-16s \n" "Addon" "Required Repo" "Needed Branch" "Local Branch" "Tracking target" "Diagnostic"
printf "%-20s | %-40s | %-16s | %-16s | %-16s | %-16s \n" "- - - - - - - - - - " "- - - - - - - - - - - - - - - - - - - - " "- - - - - - - - " "- - - - - - - - " "- - - - - - - - " "- - - - - - - - - - - - -"

# This function receives a line with the following format : NAME URL BRANCH
# Called for each addon in addons.txt
function processAddon {
  # parse arguments
  local addonName=$(echo $addon | cut -f1 -d' ')
  local addonUrl=$(echo $addon | cut -f2 -d' ')
  local addonBranch=$(echo $addon | cut -f3 -d' ')

  # define vars
  local addonRemoteUrl=''
  local addonTrackingRemote=''
  local addonLocalBranch=''

  # default return values
  local addonExists='-'
  local addonExistsCol=$style_red
  local addonRemoteIsSame='-'
  local addonRemoteIsSameCol=$style_reset
  #addonBranchIsSame='-different-'
  local addonBranchIsSameCol=$style_reset
  local addonHasLocalChanges='-'
  #addonHasLocalChangesCol=$style_normal
  local addonDiagnosticMessage=""
  local addonDiagnosticMessageCol=$style_reset

  # check id addon directory exists
  if [ -d "$addonsDir/$addonName" ]; then
    local addonExists='yes'
    local addonExistsCol=$style_green

    cd $addonsDir/$addonName

    # Parse local information
    local addonLocalBranch=`git name-rev --name-only HEAD` # ex: master (local branch name)
    local addonTrackingRemote=`git config branch.$addonLocalBranch.remote` # ex: origin (remote's local name)
    #local addonRemoteUrl=$(git config remote.$addonTrackingRemote.url) # ex: https://github.com/armadillu/ofxTimeMeasurements
    local addonRemoteUrl=$(git remote get-url $addonTrackingRemote) # alternative for the above line
    #local addonRemoteTrackingBranch=$(git rev-parse --symbolic-full-name --abbrev-ref $addonTrackingRemote) # ex: origin/master # Note: I got some unexpected values for some repos. Better not use.
    local addonRemoteTrackingBranch=$(git rev-parse --symbolic-full-name --abbrev-ref $addonLocalBranch@{upstream}) # ex: origin/master (long version)
    #local addonRemoteTrackingBranch=$(git symbolic-ref --quiet --short HEAD) # ex: master (short version)
    
    # Check for a detached head / tracking repo
    local dummyvar=$(git symbolic-ref --quiet --short HEAD) # quiet command, we use the exit code via $?
    #dummyvar=(git symbolic-ref --quiet --short no_branch_like_this); # Debug, uncomment to send exit code 1 to $?
    let addonHasDetachedHead=$? # keeps exit status of previous command. (keep this line after the previous one)
    #addonDetachedHead=$(git rev-parse --abbrev-ref HEAD) #ex: master, if tracking. Hash otherwise.

    
    #addonRemoteTrackingBranch=`git config branch.$addonLocalBranch.merge` #ex : refs/heads/master
    #addonRemoteTrackingBranch=`git symbolic-ref -q HEAD` #ex : refs/heads/master, exit code indicates tracking status.
    

    #echo "Current branch remote.name = $(git rev-parse --abbrev-ref HEAD)" # ex: master
    #echo "Entering ${mosaic_addons[$i]} @ $(git status -b -s)";
    #TRACKING_BRANCH=`git config branch.$LOCAL_BRANCH.merge` # ex: refs/heads/master

    # Check if remote URL is the same
    if [[ "$addonRemoteUrl" =~ ${addonUrl//https?\:\/\//} ]]; then
      #addonRemoteIsSame='ok'
      #addonRemoteIsSameCol=$style_green
      #addonDiagnosticMessageCol=$style_green

      # Local branch name can be different. Mark green when it's the same.
      if [[ "$addonLocalBranch" =~ $addonBranch ]]; then
        addonBranchIsSameCol=$style_green
      else
        addonBranchIsSameCol=$style_yellow
      fi

      # Check if the local branch tracks the right branch
      if [[ "$addonTrackingRemote/$addonBranch" =~ "$addonRemoteTrackingBranch" ]]; then
        #addonBranchIsSame="$addonLocalBranch"
        #addonBranchIsSameCol=$style_green
        addonRemoteIsSameCol=$style_green

        # Sync with remote(s), updates references
        # maybe use this instead ? : git remote update
        git fetch --quiet > /dev/null 2>&1 # Hides output as --quiet doesn't silence git fatal errors such as no internet.

        # Check for network errors
        let addonRemoteUnavailable=$? # keep this line directly after to git fetch

        # Check for available updates (quick method)
        lastLocalCommit=`git show --no-notes --format=format:"%H" "$addonBranch" | head -n 1`
        lastRemoteCommit=`git show --no-notes --format=format:"%H" "$addonTrackingRemote/$addonBranch" | head -n 1`
        if [ "$lastLocalCommit" != "$lastRemoteCommit" ]; then
          addonDiagnosticMessage="New commits are available, please pull this repo."
          addonDiagnosticMessageCol=$style_yellow
          addonBranchIsSameCol=$style_yellow
        else

          # Check for diffs (uncomited local changes) (or rather differences with remote ?)
          if [[ `git diff --name-only $addonLocalBranch $addonTrackingRemote/$addonBranch` ]]; then
            addonDiagnosticMessage="This repo has uncomited changes."
            addonDiagnosticMessageCol=$style_yellow

            # todo: check clean working directory ?
          fi

        fi
        # Remote unreachable
        if [ "$addonRemoteUnavailable" -gt 0 ]; then
          if [ -z "$addonDiagnosticMessage" ]; then #only set message if not already set
            addonDiagnosticMessage="The remote is unreachable."
            addonDiagnosticMessageCol=$style_yellow
          fi
        fi

      # Incorrect tracking branch
      else
        #echo "Mismatch : $addonLocalBranch is not $addonBranch"
        #echo "$addonTrackingRemote/$addonBranch VS $addonRemoteTrackingBranch"
        addonRemoteIsSameCol=$style_red
        addonDiagnosticMessage="Your local branch tracks a different branch."
        addonDiagnosticMessageCol=$style_red
        #addonBranchIsSame="/!\ $addonLocalBranch"
      fi

    else
      addonDiagnosticMessage="Your local branch tracks a different repo/url."
      addonDiagnosticMessageCol=$style_red
      addonRemoteIsSameCol=$style_red
      addonBranchIsSameCol=$style_yellow
    fi

    # warn for detached head ? (override other info for GUI only)
    if [ "$addonHasDetachedHead" -gt 0 ]; then
      addonRemoteIsSameCol=$style_yellow
      addonRemoteTrackingBranch="Detached head"
      if [ -z "$addonDiagnosticMessage" ]; then #only set message if not already set
        addonDiagnosticMessageCol=$style_red
        addonDiagnosticMessage="This local branch is not tracking any remote branch."
      fi
    fi

  else
    addonDiagnosticMessageCol=$style_red
    addonDiagnosticMessage="This addon is not installed."
    addonBranchIsSameCol=$style_red
    addonLocalBranch="-not installed-"
  fi

  # output table line with info
  #printf " %-30s | %-30s |" "$addonName" "$addonUrl"
  #printf "%-30s | %-50s | %-16s | ${addonExistsCol}%-16s${style_reset} | ${addonRemoteIsSameCol}%-16s${style_reset} | ${addonBranchIsSameCol}%-16s${style_reset} | ${addonHasLocalChangesCol}%-16s${style_reset} | %-16s " "$addonName" "$addonUrl" "$addonBranch" "$addonExists" "$addonRemoteIsSame" "$addonBranchIsSame" "$addonHasLocalChanges"
  printf "%-20s | %-40s | %-16s | ${addonBranchIsSameCol}%-16s${style_reset} | ${addonRemoteIsSameCol}%-16s${style_reset} | ${addonDiagnosticMessageCol}%-16s${style_reset} " "$addonName" "${addonUrl/https:\/\//}" "$addonBranch" "$addonLocalBranch" "$addonRemoteTrackingBranch" "$addonDiagnosticMessage"

}

#set -ex
while read addon;
do
  # ignore commented addons in addons.txt
  if (echo $addon | grep -q '#'); then
    #echo "Continue commented addon !"
    continue;
  fi
  # Skip empty lines. -z checks 0-length
  strippedAddon="${addon/ /}" # strip spaces
  strippedAddon="${strippedAddon/\t/}" # strip tabs
  strippedAddon="${strippedAddon/\r/}" # strip return
  strippedAddon="${strippedAddon/\n/}" # strip newline
  if [ -z "$strippedAddon" ]; then
    #echo "Skipping empty line !"
    continue;
  fi

  processAddon `echo $addon`
  echo ""
done < "$curDir/addons.txt"

echo ""
echo "Work = done. Enjoy. :) "
echo ""
